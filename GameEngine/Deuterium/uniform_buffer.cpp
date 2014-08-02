#include "uniform_buffer.h"
#include "string_helper.h"
namespace deuterium
{
UniformBuffer::UniformBuffer(void)
{
}


UniformBuffer::~UniformBuffer(void)
{
}

UniformBuffer::UniformBuffer(const UniformBuffer& u_buff)
{
	//TODO
	this->_name = u_buff._name;
	this->_buffer_parameter_DA = u_buff._buffer_parameter_DA;
}


S32 UniformBuffer::get_uniform_id(std::string uniform_name)
{
	for(U32 i = 0; i < this->_buffer_parameter_DA.size(); ++i)
	{
		if(StringHelper::is_identical_string(_buffer_parameter_DA[i].name(),uniform_name))
		{
			return i;
		}
	}

	//uniform does not exist
	return -1;
}

void UniformBuffer::load_uniform_buffer(UniformBuffer& uniform_buffer)
{

	for(U32 i = 0; i < uniform_buffer._buffer_parameter_DA.size(); ++i)
	{
		DeuteriumUniformType type = uniform_buffer._buffer_parameter_DA[i].type();
		std::string name = uniform_buffer._buffer_parameter_DA[i].name();

		this->add_uniform(type,name.c_str());
	}
}

void UniformBuffer::clear_uniform_buffer()
{
	_buffer_parameter_DA.clear();


	//TODO update gl context
}

void UniformBuffer::add_uniform(DeuteriumUniformType type, const char* name)
{
	ShaderParameter param;
	param.set_name(name);
	param.set_type(type);
	
	for(U32 i = 0; i < _buffer_parameter_DA.size() ;++i)
	{
		if(_buffer_parameter_DA[i].is_identical(param))
			return;
	}
	
	_buffer_parameter_DA.push_back(param);
}


void UniformBuffer::update_uniform(U32 param_id, void* value)
{
	if(param_id < _buffer_parameter_DA.size())
	{
		_buffer_parameter_DA[param_id].update_cached_parameter(value);
	}
	
}

void UniformBuffer::update_uniform(std::string uniform_name, void* value)
{
	for(U32 i = 0;  i < _buffer_parameter_DA.size(); ++i)
	{
		if(StringHelper::is_identical_string(_buffer_parameter_DA[i].name(),uniform_name))
		{
			_buffer_parameter_DA[i].update_cached_parameter(value);
		}
	}
}

}
