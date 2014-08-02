#pragma once
#include "node.h"

namespace dsm
{
class TypeNode : public Node
{
public:
	enum ShaderType {
		VERTEX = 1,
		FRAGMENT,
	};
	TypeNode(void);
	~TypeNode(void);

	bool load_content(NodeData& data);

	ShaderType type() { return _type;}
private:
	ShaderType _type;
};

}