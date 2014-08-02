#pragma once
#include "shader_component.h"
#include "json_parser.h"
#include "3rdParty\rapidjson\stringbuffer.h"
#include "3rdParty\rapidjson\document.h"
#include "3rdParty\rapidjson\writer.h"

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

	



	//compile all passes used by the RenderPipe to the current GL context
	bool compile_render_pipe();

private:
	


	std::vector<ShaderComponent> _shader_components;

};

}