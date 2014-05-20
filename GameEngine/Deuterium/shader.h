#pragma once
#include "global_data.h"

#ifdef _ANDROID_
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif
#include <string>
#include <vector>

#include "texture.h"
#include "object_container.h"
#include "shader_parameter.h"
#include "shader_component.h"
#include "string_helper.h"
#include "shader_parameter_value_settings.h"

namespace deuterium
{
	class ShaderParameterDA;
//---------------------------------------------------------------
//						Shader class definition
//---------------------------------------------------------------
class Shader
{
public:


		//-------------------------------------------------------------------
		//					Constructor / Destructor
		//-------------------------------------------------------------------
		Shader();
	virtual ~Shader();
		//ADD TEXTURE PARAMETER FOR TEXTURE?
		//-------------------------------------------------------------------
		//					Core Functions
		//-------------------------------------------------------------------

		//Load a specific shader file
		void 					load_by_file(GLenum i_ShaderType, char* i_shaderFilePath);

		//Load a specific shader through the passed content
		void					load_by_content(GLenum i_shaderType, char* i_shaderContent);


		void					load_by_component(ShaderComponent& i_shaderComponent);
		//Compile the shader program
		void 					compile();

		//Called when starting to render with the shader
		void					begin_render();

		//Called when ending the render with the shader
		void					end_render();

		//-------------------------------------------------------------------
		//						Getters / Setters
		//-------------------------------------------------------------------

		//Returns the Shader program handle
	inline	GLuint				shader_handle()	{return _shader_handle;}

			//Checks if the program has been compiled
	inline	bool				is_shader_compiled()	{return _shader_handle == 0 ? true : false;}

	inline  void				set_name(char* i_shaderName)	{ _shader_name = i_shaderName;}

	inline	char*				name() { return _shader_name;};

		//-------------------------------------------------------------------
		//						Shader Parameter functions
		//-------------------------------------------------------------------
		
		ShaderParameterValueSettings	get_empty_shader_parameter_value_settings();
		void							bind_shader_parameter_value_settings(ShaderParameterValueSettings* value_settings);

		
private:

	void update_shader_attribute_binding();
		//-------------------------------------------------------------------
		//						Helper functions 
		//-------------------------------------------------------------------
		//Checks if the ShaderParameter has a valid state inside the Shader program
		//*NOTE An unvalid state can be either unitialized or unused ShaderParameter
		bool					is_shader_parameter_valid(ShaderParameter* i_Parameter);

		//Cleans a parameter by updating its value
		//*NOTE	A program needs to be binded before using this function
		void					clean_parameter(ShaderParameter* i_Parameter);
					
		//Called at start, will fill ShaderParameters
		void					update_shader_parameter_declaration();
		//-------------------------------------------------------------------
		//						Variable declaration
		//-------------------------------------------------------------------
		//Stores the Shader program handle
		GLuint							_shader_handle;

		//Stack containing all of the sub-programs
		std::vector<ShaderComponent>	_shader_component_list;
		
		//Stores the list of parameters added to the ShaderProgram
		ObjectContainer<ShaderParameter>	_shader_parameter_list;

		
		U32								_number_of_textures_in_pass;

		char*							_shader_name;

		friend class ShaderParameterValueSettings;
};


}