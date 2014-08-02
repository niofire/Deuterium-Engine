#pragma once
#include "node.h"
#include "uniform_type.h"
namespace dsm
{
class SourceNode : public Node
{
public:
	SourceNode(void);
	~SourceNode(void);

	bool load_content(NodeData& data);

private:

	std::string content;
	std::vector<UniformType::UniformSemantic>  _semantic_vec;
};

}