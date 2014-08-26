#pragma once
#include "shader_component.h"
#include "json_parser.h"
#include "3rdParty\rapidjson\stringbuffer.h"
#include "3rdParty\rapidjson\document.h"
#include "3rdParty\rapidjson\writer.h"
#include "shader_pass.h"
#include "render_target.h"
#include "draw_request.h"
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

	//load .render_pipe file in order to assign a render proces to the RenderPipe
	bool load_render_pipe(const char* render_pipe_filename);

	void add_render_pass(RenderPass r_pass) { _render_pass_DA.push_back(r_pass);}
	
	void add_draw_request(dPtr<DrawRequest> req);

	const std::string& get_render_pass_name(U32 pass_id);
	const U32 get_render_pass_id(const std::string& name);
	void flush_draw_request();



	//compile all passes used by the RenderPipe to the current GL context
	bool compile_render_pipe();

private:
	std::vector<RenderPass> _render_pass_DA;
	std::vector<ShaderComponent> _shader_components;

};

}