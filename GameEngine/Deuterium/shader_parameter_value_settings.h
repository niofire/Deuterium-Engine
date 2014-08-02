#pragma once
#include "global_data.h"
#include "uniform_buffer.h"

namespace deuterium
{

class ShaderPass;
class ShaderParameterValueSettings
{
public:
	ShaderParameterValueSettings();
	~ShaderParameterValueSettings(void);

	//bind shader values to its associated pass
	void update_parameter(std::string param_name,void* value);
	void update_parameter(U32 param_id, void* value);
	const U32 pass_id() const {return _pass_id;}

	friend ShaderPass;
private:
	U32 _pass_id;
	UniformBuffer _uniform_buffer;
};
}
