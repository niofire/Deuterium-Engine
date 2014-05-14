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

namespace deuterium
{
class ShaderParameterAndValueArray_L;
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
			
		//Cleans all dirty parameter, hence updating the ShaderParameters into the shader program
		void					clean_dirty_parameter();
			
		//Dirties a ShaderParameter by updating its value.
		void					update_parameter(ShaderParameter::SemanticId i_Param,void* i_Value);
		void					update_parameter(char* i_ParamName, void* i_Value);
		void					update_parameter(ShaderParameterDA* i_ShaderParamAndValueArrayPtr);

		void					bind_texture_to_sampler(char* i_ParamName,Texture_L* i_Texture);
		void					bind_texture_to_sampler(ShaderParameter::SemanticId i_Param,Texture_L* i_Texture);

		void				update_shader_parameters();
		bool					contains_parameter(ShaderParameter::SemanticId i_Param);
		bool					contains_parameter(char* i_ParamName);
private:

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

		void					update_shader_attribute_binding();
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

		friend class ShaderParameterDA;
};


}