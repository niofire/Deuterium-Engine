#pragma once

#include "object_container.h"
#include "shader_parameter.h"

namespace deuterium
{
class shader;

class ShaderParameterDA
{
	struct ParameterAndValueNode
	{
		U32	_parameter_id;
		ShaderParameter		_parameter;
	};
public:
	//-------------------------------------------------
	//				constructor / destructor
	//-------------------------------------------------
	ShaderParameterDA();
	virtual ~ShaderParameterDA();
	
	//-------------------------------------------------
	//				core functions
	//-------------------------------------------------
	void	update_shader_parameter_declaration(U32 i_ShaderId);
	void	update_parameter(char* i_Name, void* value);
	void	update_parameter(ShaderParameter::SemanticId	i_ShaderId, void* value);

	void	update_shader();

	

	//access by...
	//name
	//Id
	//Parameter

	//link parameter to shader parameter order

private:
	std::vector<ParameterAndValueNode>	_parameter_and_value_DA;
	U32									_shader_id;

	

};
}