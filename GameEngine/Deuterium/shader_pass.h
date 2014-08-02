#pragma once
#include "global_data.h"
#include "uniform_buffer.h"
#include "shader_component.h"
#include "shader_parameter_value_settings.h"
//Takes in two shader components and various sampler states settings
namespace deuterium
{
class ShaderPass
{
	enum ShaderState
	{
		EMPTY,
		LOADED,
		COMPILED,
	};

	enum SamplerStates
	{
		//TODO, research
	};

	struct ShaderComponents
	{
		ShaderComponent _fragment_shader;
		ShaderComponent _vertex_shader;
	};
public:
	ShaderPass(ShaderComponent& vertex_shader,ShaderComponent& fragment_shader);
	~ShaderPass(void);

	//Merges the shader components' uniform buffers
	void update_uniform_declaration();

	//
	bool update_parameters(d_ptr<ShaderParameterValueSettings> param_val_ptr);
	
	void compile_pass();
	void compile_components();
	
	//returns a ShaderParameterValueSettings instance only if the pass is compiled.
	d_ptr<ShaderParameterValueSettings> get_parameter_and_value_setting();
	
	void set_sampler_state_flags(U32 sampler_states);
	
	void begin_pass();
	
	void end_pass();

	ShaderState shader_state() {return _shader_state;}
	std::string name() { return _pass_name;}
	void set_name(std::string name) { _pass_name = name;}
	
private:
	void update_shader_attribute_binding();
	U32 _id;
	ShaderComponents _components;
	UniformBuffer _uniform_buffer;
	ShaderParameterValueSettings _param_value_settings;
	U32 _shader_handle;
	U32 _sampler_state_flags;
	std::string _pass_name;
	ShaderState _shader_state;
};
}
