#pragma once
#include "node.h"
namespace dsm
{
class IncludeNode : public Node
{
public:
	IncludeNode(void);
	~IncludeNode(void);

	bool load_content(NodeData& data);
	std::string get_include_filename() { return _filename;}
private:
	std::string _filename;
};
}
