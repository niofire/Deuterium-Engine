#include "parser.h"
#define TAG_MISMATCH_ERROR_MSG(tag_name,line_number,file_name) "The tag "+ tag_name + " is mismatched at line "+ line_number + " of file \" " + file_name + "\""

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
		
		
		
	}

	void Parser::remove_tag(std::string& line, Node::NodeType type)
	{
		std::string str_type = this->node_to_string(type);
		//check for opening tag


		//check for bracket mismatch
		
		bool tag_remaining = true;
		
		while(tag_remaining)
		{
			
			U32 left_bracket_index = line.find("<");
			U32 right_bracket_index = line.find(">");
			U32 tag_index = line.find(type);
			if(	left_bracket_index != std::string::npos
				&& right_bracket_index != std::string::npos
				&& tag_index != std::string::npos
				&& left_bracket_index < tag_index
				&& tag_index < right_bracket_index)
			{
				line = line.substr(0,left_bracket_index) + line.substr(right_bracket_index);
			}
			else
			{
				tag_remaining = false;
			}
		}
	}

	std::vector<std::string> Parser::extract_content(U32 opening_tag_index)
	{
		std::vector<std::string> tag_content;
		
		//check if passed index contains an opening tag
		if(!is_opening_tag(_content[opening_tag_index]))
		{
			return tag_content;
		}

		Node::NodeType type = tag_type(_content[opening_tag_index]);
		int tag_guard = 0;

		for(int i = opening_tag_index; i < _content.size(); ++i)
		{
			//Add content in vector
			tag_content.push_back(_content[i]);

			if(is_opening_tag(_content[i]) && tag_type(_content[i]) == type)
			{
				//opening index corresponds to the same type as of the opening index
				tag_guard++;
			}

			if(is_closing_tag(_content[i]) && tag_type(_content[i]) == type)
			{
				//closing index corresponds to the same type as of the opening index
				tag_guard--;
			}
				
			
			if(tag_guard == 0)
			{
				//index of closing tag
				i = _content.size();
			}
			
		}

		if(tag_guard > 0)
		{
			DsmErrorStack::get_instance().push(DsmError(TAG_MISMATCH_ERROR_MSG(Parser::to_string(type),"unknown", _filename)));
			tag_content.clear();	
		}

		//remove tags from content
		if(tag_content.size() > 0)
		{
			//remove opening tag
			this->remove_tag(tag_content[0]);

			//remove closing tag
			this->remove_tag(tag_content[tag_content.size() - 1]);
		}

		return tag_content;

	}
}