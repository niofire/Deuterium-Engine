#include "type_node.h"
#include "parser.h"
namespace dsm
{

	TypeNode::TypeNode(void) : Node(TYPE)
	{
	}


	TypeNode::~TypeNode(void)
	{
	}


	bool TypeNode::load_content(NodeData& data)
	{
		std::string vertex_str		= "vertex";
		std::string fragment_str	= "fragment";

		this->_node_data = data;
		U32 type = 0;
		bool is_valid_type = true;
		for(int i = 0; i < _node_data._content.size(); ++i)
		{
			std::string str = _node_data._content[i];

			if(str.find(vertex_str) != std::string::npos)
			{
				if(type!= 0)
				{
					DsmErrorStack::get_instance().push(DsmError(DSM_ERROR_MSG(
						_node_data._filename,(""+_node_data._content_starting_index),"Invalid shader type.")));
					return false;
				}
				type = VERTEX;
			}
			if(str.find(fragment_str) != std::string::npos)
			{
				if(type!= 0)
				{
					DsmErrorStack::get_instance().push(DsmError(DSM_ERROR_MSG(
						_node_data._filename,(""+_node_data._content_starting_index),"Invalid shader type.")));
					return false;
				}
				type = FRAGMENT;
			}
		}
		_type = (ShaderType)type;
		return true;
	}
}