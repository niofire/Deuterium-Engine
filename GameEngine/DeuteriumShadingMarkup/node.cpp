#include "node.h"


namespace DSM
{
	Node::Node(NodeType type)
	{

	}

	Node::~Node()
	{
	}

	void Node::add_content(std::string content)
	{
		_node_content.push_back(content);
	}

	void Node::clear()
	{
		_node_content.clear();
		_child_nodes.clear();
	}

	void Node::add_child(d_ptr<Node> n)
	{
		_child_nodes.push_back(d_ptr<Node>(n));
	}
};