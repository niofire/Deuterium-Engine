#include "shader_manager.h"
#include "shader_parameter_DA.h"

namespace deuterium
{


char* g_defaultFragmentShaderContent = 
	"varying mediump vec3 v_norm;\n"

	"void main ()\n"
	"{\n"
	"mediump vec4 color	= vec4(v_norm,1);\n"
	"gl_FragColor = color;\n"
	"}\n";

char* g_defaultVertexShaderContent =

	"#version 110\n"
	"attribute vec3 position0;\n"
	"attribute vec3 normal;\n"
	
	"uniform mat4 pWorldViewProj;\n"
	"uniform mat4 viewproj;\n"
	
	"varying vec3 v_norm;\n"
	"void main()\n"
	"{\n"
		"v_norm = normal;\n"
		"gl_Position = pWorldViewProj *viewproj *  vec4(position0 ,1);\n"
	"}\n";


ShaderManager::ShaderManager()
{
	m_defaultShaderId = 0;

	//Create the default shader
	this->CreateShaderFromContent(m_defaultShaderId,"Default",g_defaultVertexShaderContent,g_defaultFragmentShaderContent);
}

ShaderManager::~ShaderManager()
{

}
Shader& ShaderManager::CreateShaderFromContent(U32& o_ShaderID,char* i_shaderName, char* i_vertexShaderContent, char* i_fragmentShaderContent)
{
	//Returning local variable creates undefined  behaviour...
	//Instead, return the ListObject
	Shader l_ShaderTemp;
	l_ShaderTemp.set_name(i_shaderName);
	l_ShaderTemp.load_by_content(GL_VERTEX_SHADER,i_vertexShaderContent);
	l_ShaderTemp.load_by_content(GL_FRAGMENT_SHADER,i_fragmentShaderContent);
	l_ShaderTemp.compile();
	o_ShaderID = m_ShaderContainer.add(l_ShaderTemp);
	

	Shader* l_returnedShader = m_ShaderContainer.get_at(o_ShaderID);
	
	if(l_returnedShader)
		return *l_returnedShader;
	else
		return GetDefaultShader();

	return *m_ShaderContainer.get_at(o_ShaderID);

}

Shader& ShaderManager::CreateShaderFromFile(U32& o_ShaderID, char* i_shaderName, char* i_VertexShaderFilename,char* i_FragmentShaderFilename)
{

	//Returning local variable creates undefined  behaviour...
	//Instead, return the ListObject
	Shader l_ShaderTemp;
	l_ShaderTemp.set_name(i_shaderName);
	l_ShaderTemp.load_by_file(GL_VERTEX_SHADER,i_VertexShaderFilename);
	l_ShaderTemp.load_by_file(GL_FRAGMENT_SHADER,i_FragmentShaderFilename);
	l_ShaderTemp.compile();
	o_ShaderID = m_ShaderContainer.add(l_ShaderTemp);
	

	Shader* l_returnedShader = m_ShaderContainer.get_at(o_ShaderID);
	
	if(l_returnedShader)
		return *l_returnedShader;
	else
		return GetDefaultShader();

	return *m_ShaderContainer.get_at(o_ShaderID);
}

void ShaderManager::BindShader(U32 i_ShaderID)
{
	if(!m_ShaderContainer.validate_id(i_ShaderID))
	{
		m_CurentlyBoundShaderId = i_ShaderID;
		glUseProgram(m_ShaderContainer.get_at(i_ShaderID)->shader_handle());
	}
	else
		glUseProgram(0);
}

void	ShaderManager::DestroyShader(U32 i_ShaderId)
{
	if(i_ShaderId == this->m_defaultShaderId)
		return;

	//TODO
}

Shader&	ShaderManager::GetDefaultShader()
{
	return *m_ShaderContainer.get_at(m_defaultShaderId);
}

void ShaderManager::UpdateShaderParameter(U32 i_ShaderId, ShaderParameterAndValueArray_L* sParamArray)
{
	m_ShaderContainer.get_at(i_ShaderId)->update_parameter(sParamArray);
}


Shader&	ShaderManager::GetShader(U32 i_ShaderId)
{
	//check for a valid id
	if(!m_ShaderContainer.validate_id(i_ShaderId))
		return this->GetDefaultShader();
	return *m_ShaderContainer.get_at(i_ShaderId);
}
}