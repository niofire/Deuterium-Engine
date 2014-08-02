#include "node.h"


namespace dsm
{
	Node::Node(NodeType type)
	{
		this->_type = type;
	}

	Node::~Node()
	{
	}\
	void Node::clear()
	{
		_node_data._content.clear();
		_child_nodes.clear();
	}

	void Node::add_child(d_ptr<Node> n)
	{
		_child_nodes.push_back(d_ptr<Node>(n));
	}
};