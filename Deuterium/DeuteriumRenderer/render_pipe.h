#pragma once
#include "render_pass.h"
namespace deuterium
{

//The RenderPipe class stores all of the rendering pipeline's data, mainly
// the render process and the compiled shader resources
class RenderPipe
{
	
public:
	RenderPipe(void);
	~RenderPipe(void);


	//------------------------------------------------------
	//			Initializing Functions
	//------------------------------------------------------

	//load .render_pipe file in order to assign a render proces to the RenderPipe
	bool load_render_pipe(const char* render_pipe_filename);

	//compile all passes used by the RenderPipe to the current GL context
	bool compile_render_pipe();
	//------------------------------------------------------
	//			Renderpass Functions
	//------------------------------------------------------

	// Accessor/mutator
	const	std::string&	get_render_pass_name(U32 pass_id);
	const	U32				get_render_pass_id(const std::string& name);
	void					add_render_pass(RenderPass r_pass) { _render_pass_DA.push_back(r_pass); }

	//Adds a draw request which will be distributed to one of the underlying renderpass
	void					add_draw_request( dPtr<DrawRequest> d);

	//------------------------------------------------------
	//			Rendering Functions
	//------------------------------------------------------
	void			flush_render_pipe();

private:
	std::vector<RenderPass> _render_pass_DA;
	std::vector<ShaderComponent> _shader_components;

};
}