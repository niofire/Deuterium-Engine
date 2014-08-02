#include "source_node.h"

#include "dsm_error_stack.h"
#include "parser.h"

namespace dsm
{

	SourceNode::SourceNode(void) : Node(SOURCE)
	{
		
	}


	SourceNode::~SourceNode(void)
	{

	}

	bool SourceNode::load_content(NodeData& data)
	{
		//cycle through all source content,
		this->_node_data = data;
		for(int i = 0; i < data._content.size(); ++i)
		{
			std::string str = data._content[i];
			//check for semantic
			std::vector<UniformType::USemantic> semantic_vec = UniformType::string_to_semantic(str);
			if(semantic_vec.size() > 0)
			{
				UniformType::UniformSemantic sem;
				
				std::vector<UniformType::UType> type_vec =  UniformType::string_to_type(str);
				
				if(type_vec.size() < 1)
				{
					//undefined type for semantic
					DsmErrorStack::get_instance().push(DsmError(DSM_ERROR_MSG(
				_node_data._filename,(""+_node_data._content_starting_index),"A shader can only have one type.")));
					return false;
				}

				//get the uniform name
				std::string uniform_name = str;
				std::string type_str = UniformType::type_to_string(type_vec[0]);
				int type_str_index = uniform_name.find(type_str);
				if(type_str_index == std::string::npos)
				{
					DsmErrorStack::get_instance().push(DsmError(DSM_ERROR_MSG(
				_node_data._filename,(""+_node_data._content_starting_index),"No type detected.")));
					return false;
				}
				
				uniform_name = uniform_name.substr(type_str_index + type_str.size()+1);
				Parser::trim(uniform_name);
				int colon_index = uniform_name.find(':');
				uniform_name = uniform_name.substr(0,colon_index);
				Parser::trim(uniform_name);
				
				
				sem._uniform._type = type_vec[0];
				sem._semantic_name = semantic_vec[0];
				sem._uniform._uniform_name = uniform_name;

				_semantic_vec.push_back(sem);

				//remove semantic notation from shader source

				this->_node_data._content[i] = str.substr(0,str.find(':')) + ";";

			}
			

		}

	}
}