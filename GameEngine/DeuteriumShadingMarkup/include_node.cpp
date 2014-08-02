#include "include_node.h"
#include "parser.h"
namespace dsm
{

	IncludeNode::IncludeNode() : Node(INCLUDE)
	{
		_filename = "";
	}

	IncludeNode::~IncludeNode()
	{

	}

	bool IncludeNode::load_content(NodeData& data)
	{
		this->_node_data = data;
		for(int i = 0; i < _node_data._content.size(); ++i)
		{
			std::string str = _node_data._content[i];

			Parser::trim(str);
			_filename = str + ".shader_extension";	
		}
		
		return true;
	
	}
}