#pragma once

#include "3rdParty\rapidjson\stringbuffer.h"
#include "3rdParty\rapidjson\document.h"
#include "3rdParty\rapidjson\writer.h"
#include "3rdParty\rapidjson\error\en.h"
#include "uniform_buffer.h"
#include "shader_extension.h"
#include "shader_pass.h"
#include "assets.h"

#include "json_parser.h"
namespace deuterium
{

class ResourceLoader
{
public:
	struct RenderingResources
	{
		Assets<ShaderPass> _shader_pass_assets;
		Assets<RenderTarget> _render_target_assets;
		Assets<UniformBuffer> _uniform_buffer_assets;
		Assets<ShaderExtension> _shader_extension_assets;
		Assets<ShaderComponent> _shader_component_assets;
	};

	ResourceLoader(void);
	~ResourceLoader(void);

	bool load_render_assets(const char* filename);

	RenderingResources get_rendering_resouces() { return _rendering_resources;}
	
	

private:

	bool load_shader_data(const char* filename);
	bool load_shader_extension(const char* shader_extension_filename);
		//load a uniform buffer from 
	bool load_uniform_buffer(const rapidjson::Value& json_element, const char* filename);
	bool load_uniform_buffer(const rapidjson::Value& json_element, const char* filename, const char* ubuffer_name);
	bool load_render_targets(const rapidjson::Value& json_element);
	bool load_shader_component(const rapidjson::Value& json_element);

	RenderingResources _rendering_resources;


	

};

}
