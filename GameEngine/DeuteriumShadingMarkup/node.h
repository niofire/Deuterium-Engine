#pragma once
#include <string>
#include <vector>
#include "../Deuterium/d_ptr.h"
namespace dsm
{
class Node
{
public:
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
	void add_child(d_ptr<Node>);
	NodeType type() {return _type;}


	std::vector< d_ptr<Node> >& get_child_nodes() {return _child_nodes; }
	void clear();


	
private:
	NodeType _type;
	std::vector<std::string> _node_content;
	std::vector<d_ptr<Node> > _child_nodes;
};
}

