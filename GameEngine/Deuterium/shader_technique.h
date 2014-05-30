#pragma once
#include "global_data.h"
#include "shader_pass.h"
#include "shader_parameter_value_settings.h"
#include <vector>

namespace deuterium
{
class ShaderTechnique
{
public:
	ShaderTechnique(void);
	ShaderTechnique(const char* name);

	~ShaderTechnique(void);
	
	void	set_name(const char* name);
	const char*	name()	{return _technique_name;}
	void	add_pass(ShaderPass* pass);
	void	set_starting_pass(U32 pass_number);
	bool	has_remaining_pass()	{ return _current_pass >= _shader_pass_list.size();}
	void	set_next_pass();
	U32		total_number_of_pass()	{return _shader_pass_list.size();}
	ShaderPass*	get_pass(U32 pass_number);
	ShaderParameterValueSettings get_parameter_value_settings();

private:
	const char*	_technique_name;
	U32		_current_pass;
	std::vector<ShaderPass*> _shader_pass_list;
};
}
