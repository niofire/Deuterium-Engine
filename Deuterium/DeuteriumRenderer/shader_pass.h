#pragma once
#include "shader_component.h"
#include "material.h"
//Takes in two shader components and various sampler states settings
namespace deuterium
{
class ShaderPass
{
public:
	//-------------------------------------------------
	//				Struct / Enum Declaration
	//-------------------------------------------------
	enum PassType
	{
		MESH_PASS,
		FULLSCREEN_PASS,
		LIGHT_PASS,
	};

	enum SamplerStates
	{
		//TODO, research
	};

	struct ShaderProgram
	{
		U32				_shader_handle;
		ShaderComponent _fragment_shader;
		ShaderComponent _vertex_shader;
	};
public:
	
	//-------------------------------------------------
	//				Constructor / Destructor
	//-------------------------------------------------
	ShaderPass();
	ShaderPass(const ShaderPass& p);
	ShaderPass(ShaderComponent& vertex_shader,ShaderComponent& fragment_shader);
	~ShaderPass(void);


	//-------------------------------------------------
	//				Initialization Functions
	//-------------------------------------------------
	bool	compile_pass();

	//Compile the vertex and fragment shader components
	//returns false if compilation does not succeed
	bool	compile_components();

	//-------------------------------------------------
	//				Rendering Functions
	//-------------------------------------------------
	
	void	begin_pass();
	void	end_pass();
	void	set_sampler_state_flags(U32 sampler_states);
	void	bind_material(const Material& m);
	
	PassType	type() { return _type; }

	
private:
	U32 _id;
	ShaderProgram _shader;
	U32 _sampler_state_flags;
	std::string _pass_name;
	PassType _type;
};
}