#pragma once

#include "global_data.h"
#include "string_helper.h"
#include <vector>

namespace deuterium
{
class ShaderComponent
{

public:
	ShaderComponent(void);
	~ShaderComponent(void);


	void load_by_file(GLenum i_shaderType, char* i_filePath);

	void load_by_content(GLenum i_shaderType, char* i_filePath);

	void compile();

	void delete_and_uncache();

	const U32	 component_handle() const {return _component_handle;}
	const std::vector<std::string> component_content() const {return _shader_content;}


private:
	std::vector<std::string> _shader_content;
	char* _shader_filename;
	GLenum _shader_type;
	bool	_is_compiled;
	U32	_component_handle;

};
}
