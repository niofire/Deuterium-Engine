#include "parser.h"
#include "uniform_type.h"
#define TAG_MISMATCH_ERROR_MSG(tag_name,line_number,file_name) "The tag "+ tag_name + " is mismatched at line "+ line_number + " of file \" " + file_name + "\""
#define TAG_DOES_NOT_EXIST(tag_name,filename) "The tag " + tag_name  + " does not exists."
namespace dsm
{

	Parser::Parser(void)
	{

	}


	Parser::~Parser(void)
	{
	}

	std::vector<DsmTag> Parser::get_tag_tree()
	{
		std::vector<DsmTag> tag_tree;	
		return tag_tree;
	}



	void Parser::remove_tag(std::string& line, Node::NodeType type)
	{

		std::vector<std::string> str_vec = this->get_tags_from_string(line);

		for(int i = 0; i < str_vec.size(); ++i)
		{
			//only remove valid tags
			if(!is_tag_type(str_vec[i],Node::NUMBER_OF_TAGS_NULL))
			{
				//remove tag
				U32 left_bracket_index = line.find("<");
				U32 right_bracket_index = line.find(">");
				line = line.substr(0,left_bracket_index) + line.substr(right_bracket_index+1);
			}
		}
		
	}

	bool Parser::has_tag_integrity()
	{
		std::stack<Node::NodeType> nodetype_stack;

		for(int i = 0; i < _content.size(); ++i)
		{
			//check for valid tags
			
			std::vector<std::string> tags = get_tags_from_string(_content[i]);
			std::string str;
			for(int j = 0; j < tags.size(); ++j)
			{
				str = tags[j];
				if(is_tag_type(str,Node::NUMBER_OF_TAGS_NULL))
				{
					return false;
				}

				//check for tag mismatch
			if(this->is_opening_tag(str))
			{
				nodetype_stack.push(tag_type(str));
			}
			if(this->is_closing_tag(str))
			{
				if(!is_tag_type(str,nodetype_stack.top()))
				{
					//Tag mismatch
					DsmErrorStack::get_instance().push(DsmError(TAG_MISMATCH_ERROR_MSG(node_to_string(tag_type(str)),(""+i),_filename)));
					return false;
				}
				nodetype_stack.pop();
			}

			}
			
			
		}

		


		return true;
	}

	std::vector< Node::NodeData > Parser::extract_content(Node::NodeType node_type)
	{
		std::vector<Node::NodeData > tag_content;
		if(!has_tag_integrity())
			return tag_content;

		int tag_guard = 0;
		for(int i = 0; i < _content.size(); ++i)
		{
			//check if content has an opening tag of the passed node_type
			if(is_opening_tag(_content[i]) && is_tag_type(_content[i],node_type))
			{

				Node::NodeData node_data;
				node_data._content_starting_index = i;
				bool is_inside_node = true;
				for(; is_inside_node && i < _content.size(); ++i)
				{
					node_data._content.push_back(_content[i]);

					if(is_opening_tag(_content[i]) && is_tag_type(_content[i],node_type))
					{
						tag_guard++;
					}

					if(is_closing_tag(_content[i]) && is_tag_type(_content[i],node_type))
					{
						//closing index corresponds to the same type as of the opening index
						tag_guard--;
					}

					if(tag_guard < 1)
					{
						is_inside_node  = false;
					}
				}
				
				tag_content.push_back(node_data);

				//remove opening and closing tags of 
				for(int i = 0; i < tag_content.size(); ++i)
				{
					if(tag_content[i]._content.size() > 0)
					{
						this->remove_tag(tag_content[i]._content[0],node_type);
						this->remove_tag(tag_content[i]._content[tag_content[i]._content.size() - 1],node_type);
					}
				}


			}
		}
		return tag_content;
	}

	bool Parser::is_opening_tag(std::string& str)
	{
		//opening tag => < some_tag_name >
		std::vector<std::string> tags = Parser::get_tags_from_string(str);

		for(int i = 0; i < tags.size(); ++i)
		{

		int left_bracket_index = str.find("<");
		int right_bracket_index = str.find(">");
		if(left_bracket_index != std::string::npos			// no left bracket present
			&& right_bracket_index != std::string::npos		// no right bracket present
			&& left_bracket_index < right_bracket_index		//right bracket before left bracket
			&& str[left_bracket_index+1] != '/')			//closing bracket
			return true;
		}

		//check if closing index


		return false;
	}

	bool Parser::is_closing_tag(std::string& str)
	{
		std::vector<std::string> tags = Parser::get_tags_from_string(str);
		for(int i = 0; i < tags.size(); ++i)
		{
		int left_bracket_index = tags[i].find("</");
		int right_bracket_index = tags[i].find(">");
		if(left_bracket_index != std::string::npos			
			&& right_bracket_index != std::string::npos		
			&& left_bracket_index < right_bracket_index)	
			return true;
		}
		return false;
	}

	std::vector<U32> Parser::find_substr_indexes(std::string original_str, const char* searched_str)
	{
		std::string substr(searched_str);
		std::vector<U32> indexes_vec;
		U32 index = 0;
		U32 previous_index = 0;
		U32 instances = 0;
		while(index != std::string::npos)
		{
			index = original_str.find(substr);
			if(index != std::string::npos)
			{
				indexes_vec.push_back(index + previous_index);
				original_str = original_str.substr(index + substr.size());
				previous_index += index + substr.size();
			}
		}
		return indexes_vec;
	}

	std::string Parser::node_to_string(Node::NodeType type)
	{

		switch(type)
		{
		case Node::SHADER:
			return "shader";
		case Node::NAME:
			return "name";
		case Node::SAMPLER:
			return "sampler";
		case Node::INCLUDE:
			return "include";
		case Node::UNIFORM_BUFFER:
			return "uniform_buffer";
		case  Node::TYPE:
			return "type";
		case  Node::SOURCE:
			return "source";
		case  Node::FRAGMENT:
			return "fragment";
		case  Node::VERTEX:
			return "vertex";
		case  Node::RENDER_STATE:
			return "render_state";
		case  Node::PASS:
			return "pass";
		case  Node::TECHNIQUE:
			return "technique";
		case  Node::SHADER_EXTENSION:
			return "shader_extension";
		case  Node::RENDER_ASSETS_PACKAGE:
			return "render_assets_package";
		case Node::RELATIVE:
			return "relative";
		case Node::ABSOLUTE:
			return "absolute";
		case Node::RESOURCE:
			return "resource";
		case Node::RENDER_TARGET:
			return "render_target";
		case Node::WIDTH:
			return "width";
		case Node::HEIGHT:
			return "height";
		case Node::FORMAT:
			return "format";
		case Node::RENDER_PIPE:
			return "render_pipe";
		case Node::INPUT:
			return "input";
		case Node::OUTPUT:
			return "output";
		default:
			return "invalid";
		}
	}
	std::vector<UniformType::UType> Parser::get_uniform_type(std::string& str)
	{
		return UniformType::string_to_type(str);
	}

	bool Parser::is_tag_type(std::string& str, Node::NodeType type)
	{
		return tag_type(str) == type;
	}

	std::vector<std::string> Parser::get_tags_from_string(std::string& str)
	{
		std::vector<std::string> str_vec;
		std::vector<U32> indexes = find_substr_indexes(str,"<");
		for(int i = 0; i < indexes.size(); ++i)
		{
			int closing_bracket = str.substr(indexes[i] + 1).find(">");
			if(closing_bracket != std::string::npos)
			{
				str_vec.push_back(str.substr(indexes[i],closing_bracket + 2));
			}
		}
		return str_vec;
	}


	void	Parser::trim_front(std::string& l_String)
{
	
	while(l_String.length() > 0 && l_String.find_first_of(" ") == 0)
		l_String = l_String.substr(1);
	
}

void Parser::trim_end(std::string& l_String)
{
	while(l_String.length() > 0 && l_String.find_last_of(" ") == l_String.size() - 1)
		l_String.erase(l_String.find_last_of(" "),1);
}

void	Parser::trim(std::string& l_String)
{
	//Trim front and end
	trim_front(l_String);
	trim_end(l_String);
}

	Node::NodeType Parser::tag_type(std::string& str)
	{
		std::vector<std::string> str_vec =  get_tags_from_string(str);

		if(str_vec.empty())
		{
			return Node::NUMBER_OF_TAGS_NULL;
		}
		if(is_opening_tag(str))
		{
			//remove brackets
			std::string s = str;
			s = str.substr(str.find("<") + 1, str.find(">") - str.find("<") - 1);
			trim(s);

			for(int i = 0; i < Node::NUMBER_OF_TAGS_NULL; ++i)
			{
				if(!(s.compare(node_to_string((Node::NodeType)i))))
					return (Node::NodeType)i;
			}
		}
		else if(is_closing_tag(str))
		{
			//remove brackets
			std::string s = str;
			s = str.substr(str.find("<") + 2, str.find(">") - str.find("<") - 2);
			trim(s);

			for(int i = 0; i < Node::NUMBER_OF_TAGS_NULL; ++i)
			{
				if(!(s.compare(node_to_string((Node::NodeType)i))))
					return (Node::NodeType)i;
			}
		}

		//tag does not exists, error.
		
		DsmErrorStack::get_instance().push(DsmError(TAG_DOES_NOT_EXIST(str_vec[0])));

		return Node::NUMBER_OF_TAGS_NULL;

		
	}




}
