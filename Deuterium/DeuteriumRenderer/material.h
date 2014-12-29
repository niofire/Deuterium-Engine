#pragma once
#include <vector>
#include "shader_parameter.h"
#include "d_typedef.h"
namespace deuterium
{

	class Material
	{

	public:
		Material();
		~Material();


		//-----------------------------------------------------
		//				Material Operations
		//-----------------------------------------------------
		void	bind_material() const ;
		void	unbind_material() const;

		//-----------------------------------------------------
		//				ShaderParameter Operations
		//-----------------------------------------------------
		ShaderParameter* get_parameter_by_name(const char* name);
		ShaderParameter* get_parameter_by_id(const U32& id);

		//Add a shader parameter to the material. 
		void add_shader_parameter(ShaderParameter p);


		//----------------------------------------------------
		//				Texture Operations
		//----------------------------------------------------
		void add_texture(U32 texture_handle);

	private:
		std::vector<U32> _texture_handle_DA;
		std::vector<ShaderParameter> _parameterDA;
	};

}