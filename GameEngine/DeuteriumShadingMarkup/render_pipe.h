#pragma once
#include "common.h"
#include "../Deuterium/d_ptr.h"
#include <vector>
#include "node.h"
namespace dsm
{
class RenderPipe
{
public:
	RenderPipe(void);
	~RenderPipe(void);

	U32 num_shaders();
	U32 num_techniques();
	U32 num_pass();

	std::vector< d_ptr<Node> >& get_shader_nodes();
	std::vector< d_ptr<Node> >& get_technique_nodes();
	std::vector< d_ptr<Node> >& get_pass_nodes();
	std::vector< d_ptr<Node> >& get_resouce_nodes();


	//get the render_pipe nodes in their respective order of execution
	std::vector< d_ptr<Node> >& get_render_nodes();
};

}