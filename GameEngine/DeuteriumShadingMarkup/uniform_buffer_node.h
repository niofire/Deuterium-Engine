#pragma once
#include "node.h"
#include "uniform_type.h"
namespace dsm
{
class UniformBufferNode : public Node
{

public:
	UniformBufferNode();
	~UniformBufferNode();

	bool load_content(Node::NodeData& data);
private:
	std::vector<UniformType::Uniform> _uniform_list;
};

}