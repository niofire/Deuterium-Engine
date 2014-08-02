#pragma once

#include "global_data.h"
#include "string_helper.h"
#include <vector>
#include "uniform_buffer.h"
#include "shader_extension.h"
#include "shader_parameter.h"

namespace deuterium
{
class ShaderComponent
{
	struct AttributeLocation
	{
		AttributeLocation(U32 attrib_location, std::string attrib_name)
		{
			_attrib_location = attrib_location;
			_attrib_name = attrib_name;
		}
			U32 _attrib_location;
			std::string _attrib_name;
	};

	struct ShaderComponentData
	{
		GLenum _shader_type;
		std::string _shader_content;
		std::vector<d_ptr<ShaderExtension>> _shader_extensions_DA;
		std::vector<d_ptr<UniformBuffer> > _constant_uniform_buffer_DA;
		d_ptr<UniformBuffer>  _dynamic_uniform_buffer;
		std::vector<AttributeLocation> _attribute_location;
		std::string _name;
		
		
	};
public:
	ShaderComponent();
	~ShaderComponent(void);

	void load_by_content(std::vector<std::string> file_content);
	void compile();
	void delete_and_uncache();

	const U32	 component_handle() const {return _component_handle;}
	const std::string source() const {return _data._shader_content;}

	void set_name(std::string& name) { _data._name = name;}
	void set_type(GLenum type) {_data._shader_type = type;}
	U32	type()	{return _data._shader_type;}
	void set_source(std::string str) { _data._shader_content = str;}
	std::string name() { return _data._name;}

	void add_constant_uniform_buffer(const d_ptr<UniformBuffer>& buffer) { _data._constant_uniform_buffer_DA.push_back(buffer);}
	void set_dynamic_uniform_buffer(d_ptr<UniformBuffer>& buffer) { _data._dynamic_uniform_buffer = buffer;}
	void add_source_extension(const d_ptr<ShaderExtension>& ext) { _data._shader_extensions_DA.push_back(ext);}
	void add_attribute_location(StreamType type, const char* name);

	std::vector<d_ptr<UniformBuffer> >& get_constant_uniform_buffer() {return _data._constant_uniform_buffer_DA;}
	d_ptr<UniformBuffer> get_dynamic_uniform_buffer() {return _data._dynamic_uniform_buffer;}


private:
	
	
	
	ShaderComponentData _data;
	
	bool	_is_compiled;
	U32	_component_handle;

};
}
