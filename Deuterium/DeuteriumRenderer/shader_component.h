#pragma once

#include "global_data.h"
#include "string_helper.h"
#include <vector>
#include "uniform_buffer.h"
#include "shader_extension.h"
#include "shader_parameter.h"
#include "stream_data.h"

namespace deuterium
{
class ShaderComponent
{

	struct AttributeLocation
	{
		AttributeLocation(U32 attrib_stream_type, std::string attrib_name)
		{
			_attrib_stream_type = attrib_stream_type;
			_attrib_name = attrib_name;
		}
			U32 _attrib_stream_type;
			std::string _attrib_name;
	};

	struct ShaderComponentData
	{
		GLenum _shader_type;
		std::string _shader_content;
		std::vector<AttributeLocation>		_attribute_location_DA;
		std::string							_name;		
	};

public:
	ShaderComponent();
	~ShaderComponent(void);

	//-------------------------------------------------
	//				Initialization Functions
	//-------------------------------------------------
	void load(std::vector<std::string>& file_content);
	void compile();

	//-------------------------------------------------
	//				Accessor / Mutators
	//-------------------------------------------------
	
	//Name of the shader, is unique.
	void	set_name(std::string& name) { _data._name = name;}
	const	std::string& name() const { return _data._name;}

	//The shader source code used to compile the component
	void	set_source(std::string str) { _data._shader_content = str;}
	const	std::string source() const {return _data._shader_content;}

	//Shader type, either GL_VERTEX or GL_FRAGMENT
	void	set_type(GLenum type) {_data._shader_type = type;}
	U32		type()	{return _data._shader_type;}

	//The ShaderComponent rendering handle
	const	 U32 handle() const {return _component_handle;}
	
	//-------------------------------------------------
	//				Shader Handling function
	//-------------------------------------------------
	void add_attribute_location(StreamType type, const char* name);
	void bind_shader_attribute(U32 shader_handle);


private:
	ShaderComponentData _data;
	bool	_is_compiled;
	U32	_component_handle;

};
}
