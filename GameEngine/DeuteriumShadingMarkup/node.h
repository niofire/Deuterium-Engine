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
		NUMBER_OF_TAGS_NULL,
	};
	
	class NodeData
	{
	public:
		NodeData()
		{
			_filename = "";
			_content_starting_index = 0;
		}

		NodeData(const NodeData& n)
		{
			this->_filename = n._filename;
			this->_content = n._content;
			this->_content_starting_index = n._content_starting_index;
		}
		
		~NodeData()
		{

		}

		std::vector<std::string> _content;
		std::string _filename;
		int _content_starting_index;
	};
public:
	Node(NodeType type);
	virtual ~Node(void);

	virtual bool load_content(NodeData& data) = 0;
	void add_child(d_ptr<Node>);
	NodeType type() {return _type;}


	std::vector< d_ptr<Node> >& get_child_nodes() {return _child_nodes; }
	void clear();


	
protected:
	NodeType _type;
	NodeData _node_data;
	std::vector<d_ptr<Node> > _child_nodes;
};
}

