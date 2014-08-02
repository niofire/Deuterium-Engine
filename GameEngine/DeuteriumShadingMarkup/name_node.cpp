#include "name_node.h"
#include "parser.h"
namespace dsm
{

	NameNode::~NameNode()
	{

	}


	bool NameNode::load_content(NodeData& data)
	{
		this->_node_data = data;
		for(int i = 0; i < _node_data._content.size(); ++i)
		{
			std::string str = _node_data._content[i];

			Parser::trim(str);
			if(str.size() != 0)
			{
				if(this->_name.size() == 0)
				{
					this->_name = str;
				}
				else
				{
					this->_name += " " + str;
				}
				
			}
		}
		return true;
	}
}