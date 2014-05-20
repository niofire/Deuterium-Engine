#pragma once
#include "global_data.h"

namespace deuterium
{
class ShaderParameterValueSettings
{
		struct ParameterAndValueNode
	{
		U32	_parameter_id;
		ShaderParameter		_parameter;
	};

public:
	ShaderParameterValueSettings();
	~ShaderParameterValueSettings(void);

	void		bind_values_to_shader(U32 shader_handle);
	void		udpate_shader_parameter_declaration(U32 shader_handle);

	bool		update_value(char* parameter_name, void* value);
	bool		update_value(U32   parameter_id, void* value);
	U32			parameter_id(char* parameter_name);
	const char*	parameter_name(U32 parameter_id);

private:
	U32		last_bound_shader_handle;
	std::vector<ParameterAndValueNode>	_shader_parameter_value_node_DA;
};
}
