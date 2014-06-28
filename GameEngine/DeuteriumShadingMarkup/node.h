#pragma once
#include <string>
#include <vector>
namespace DSM
{
class Node
{
	enum NodeType
	{
		SHADER,
		NAME,
		SAMPLER,
		INCLUDE,
		UNIFORM_BUFFER,
		TYPE,
		SOURCE,
		FRAGMENT,
		VERTEX,
		RENDER_STATE,
		PASS,
		TECHNIQUE,
		SHADER_EXTENSION,
		RENDER_ASSETS_PACKAGE,
		RELATIVE,
		ABSOLUTE,
		RESOURCE,
		RENDER_TARGET,
		WIDTH,
		HEIGHT,
		FORMAT,
		RENDER_PIPE,
		INPUT,
		OUTPUT,
	};
public:
	Node(NodeType type);
	~Node(void);

	void add_content(std::string);
	void clear();
private:
	NodeType _type;
	std::vector<std::string> _node_content;
	std::vector<Node*> _child_nodes;
};
}

