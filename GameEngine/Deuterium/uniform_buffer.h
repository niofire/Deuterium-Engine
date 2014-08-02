#pragma once
#include "global_data.h"
#include "shader_parameter.h"
#include "uniform_type_handler.h"
#include <vector>
namespace deuterium
{
class UniformBuffer
{
public:


	UniformBuffer(void);
	~UniformBuffer(void);

	UniformBuffer(const UniformBuffer& u_buff);


	void init();

	//Load the passed uniform buffer into this uniform buffer. Ignores repeated shader parameters
	void load_uniform_buffer(UniformBuffer& uniform_buffer);

	//remove all ShaderParameters loaded in this uniformbuffer and updates the GL content
	void clear_uniform_buffer();

	void add_uniform(DeuteriumUniformType type, const char* name);

	//Update the uniform with the passed id
	void update_uniform(U32 param_id,void* value);

	//Update the uniform with its name, considerably slower than updating with id
	void update_uniform(std::string uniform_name,void* value);

	//returns -1 if uniform does not exist
	S32 get_uniform_id(std::string uniform_name);


	//TODO
	std::string to_shader_content_string(std::string block_name) {return block_name;}


	void set_name(std::string name) { _name = name;}
	std::string name() { return _name;}
private:
	std::string _name;
	std::vector<ShaderParameter> _buffer_parameter_DA;

};
}
