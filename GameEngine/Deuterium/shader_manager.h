#pragma once
#include "object_container.h"
#include "shader.h"
#include "global_data.h"

namespace deuterium
{
class ShaderParameterAndValueArray_L;
class ShaderManager
{
public:
						ShaderManager();
	virtual				~ShaderManager();
	Shader&			CreateShaderFromFile(U32& o_ShaderId,char* i_shaderName, char* i_VertexShaderFilename,char* i_FragmentShaderFilename);
	Shader&			CreateShaderFromContent(U32& o_ShaderId,char* i_shaderName, char* i_VertexShaderFilename,char* i_FragmentShaderFilename);
	void				DestroyShader(U32 i_ShaderID);	
	void				UpdateShaderParameter(U32 i_ShaderId,ShaderParameterAndValueArray_L* i_ShaderParamAndValueArray);
	void				BindShader(U32 i_ShaderID);
	Shader&			GetShader(U32 i_ShaderID);

private:
	Shader&			GetDefaultShader();
	U32					m_defaultShaderId;
	U32								m_CurentlyBoundShaderId;
	
	ObjectContainer<Shader>		m_ShaderContainer;
};


}