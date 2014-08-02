#pragma once
#include "node.h"
namespace dsm
{
class NameNode : public Node
{
public:
	NameNode(void) : Node(NAME) {_name = "";}
	~NameNode(void);

	bool load_content(NodeData& data);

	std::string get_name() { return _name;}

private:
	std::string _name;
};

}