#include "uniform_buffer_node.h"
#include "parser.h"

namespace dsm
{
	UniformBufferNode::UniformBufferNode(void) : Node(UNIFORM_BUFFER)
	{
	}


	UniformBufferNode::~UniformBufferNode(void)
	{
	}

	bool UniformBufferNode::load_content(Node::NodeData& data)
	{
		this->_node_data = data;
		for(int i = 0; i < _node_data._content.size(); ++i)
		{
			std::string str = _node_data._content[i];
			Parser::trim(str);

			std::vector<UniformType::UType> type_vec = Parser::get_uniform_type(str);
			for(int j = 0; j < type_vec.size(); ++j)
			{
				//get name
				std::string type_str = UniformType::type_to_string(type_vec[j]);
				int type_str_index  = str.find(type_str);
				
				if(type_str_index != std::string::npos)
				{

					//remove type
					str = str.substr(type_str_index + type_str.size()+1);
					Parser::trim(str);
					int semi_colon_index = str.find(';');


					if(semi_colon_index == std::string::npos)
					{
						DsmErrorStack::get_instance().push(DsmError(DSM_ERROR_MSG(_node_data._filename,(""+_node_data._content_starting_index),"Semi-colon ';' is missing.")));
						return false;
					}

					//get name
					str = str.substr(0,semi_colon_index);
					Parser::trim(str);

					if(str.size() == 0)
					{
						DsmErrorStack::get_instance().push(DsmError(DSM_ERROR_MSG(_node_data._filename,(""+_node_data._content_starting_index),"Invalid uniform variable name.")));
						return false;
					}
					UniformType::Uniform temp_uniform;
					temp_uniform._type = type_vec[j];
					temp_uniform._uniform_name = str;
					this->_uniform_list.push_back(temp_uniform);
					


				}
				

			}
			
		}
		return true;
	}
	
}