#pragma once
#include "global_data.h"


//Takes in two shader components and various sampler states settings
namespace deuterium
{
	class ShaderParameterValueSettings;
	class Shader;
class ShaderPass
{
	enum SamplerStates
	{

	};
public:
	ShaderPass(void);
	~ShaderPass(void);

	void set_shader(U32 shader_handle);
	
	void set_parameter_value_setting(ShaderParameterValueSettings* param_value_settings);
	void set_sampler_state_flags(U32 sampler_states);
	void begin_pass();
	void end_pass();
	Shader*	bound_shader()	{return _shader;}

private:
	Shader* _shader;
	ShaderParameterValueSettings* _param_value_settings;
	U32 _sampler_state_flags;
};
}
