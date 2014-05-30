#pragma once
#include "global_data.h"

namespace deuterium
{
	class ShaderTechnique;
class ShaderParameterValueSettings
{
public:
	ShaderParameterValueSettings();
	~ShaderParameterValueSettings(void);

	//bind shader values to its associated pass
	void		bind_pass(U32 pass_number, ShaderPass* pass);

	void		update_shader_parameter_declaration(ShaderTechnique* shader_technique);

	bool		update_value(U32 pass_number,char* parameter_name, void* value);
	bool		update_value(U32 pass_number, ShaderParameter::ShaderSemantic shader_semantic, void* value);

private:
	U32		_last_bound_shader_handle;
	std::vector< std::vector<ShaderParameter::ShaderSemantic,U32> > _shader_semantic_mapping;
	std::vector< std::vector<ShaderParameter> >	_shader_parameter_value_DA;
};
}
