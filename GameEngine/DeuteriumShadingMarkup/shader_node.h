#pragma once
#include "node.h"
namespace dsm
{
class ShaderNode : public Node
{
public:
	ShaderNode(void) : Node(SHADER) {}
	~ShaderNode(void);

	bool load_content(NodeData& data);
};
}
