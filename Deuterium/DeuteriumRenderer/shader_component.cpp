#include "shader_component.h"
#include "stream_data.h"
#include <iostream>
#include <fstream>
#include "shader_component_meta_node.h"
#include "stream_data.h"
namespace deuterium
{
ShaderComponent::ShaderComponent()
{
	_component_handle = 0;
	_is_compiled = false;
}


ShaderComponent::~ShaderComponent(void)
{
}

U32 ShaderComponent::type()
{
	if(_metaPtr.is_null())
		return 0;
	
	dPtr<ShaderComponentMetaNode> nodePtr = meta_ptr();
	
	switch(nodePtr->type())
	{
	case ShaderComponentMetaNode::VERTEX:
		return GL_VERTEX_SHADER;
		break;
	case ShaderComponentMetaNode::FRAGMENT:
		return GL_FRAGMENT_SHADER;
		break;
	default:
		return 0;
	}
	return 0;
}



const std::string& ShaderComponent::name()
{
	if(_metaPtr.is_null())
		return "";
	
	dPtr<ShaderComponentMetaNode> nodePtr = meta_ptr();
	return nodePtr->name();
}

void ShaderComponent::compile(U32 id)
{

	IAsset::compile(id);
	
	dPtr<ShaderComponentMetaNode> node_ptr = meta_ptr();
	
	//Content of shader program
	const char* shader_content = node_ptr->content().c_str();
	
	//Shader type, either Fragment or Vertex
	GLenum type	= (GLenum)this->type();

	//Attribute location dynamic array, used for Vertex shader (pos, norms, texcoords, etc..)


	//compile it
	int length = strlen(shader_content);
	_component_handle = glCreateShader(type);
	glShaderSource(_component_handle,1, &shader_content,&length);
	glCompileShader(_component_handle);

	//Get Info Log for error logging
	int infoLogLength = 0;
	int maxLength = 0;

	glGetShaderiv(_component_handle,GL_INFO_LOG_LENGTH, &maxLength);
	std::vector<char> infoLog(maxLength);
	glGetShaderInfoLog(_component_handle,maxLength, &infoLogLength, &infoLog[0]);
	std::string temp = &infoLog[0];


	//Display Info Log
	if(type == GL_VERTEX_SHADER)
		std::cerr << "Vertex Shader:" << temp << std::endl;
	else if(type == GL_FRAGMENT_SHADER)
		std::cerr << "Fragment Shader:" << temp << std::endl;
}


void ShaderComponent::bind_shader_attribute(U32 shader_handle)
{
	dPtr<ShaderComponentMetaNode> node_ptr = meta_ptr();
	const std::vector<ShaderComponentMetaNode::AttributeLocation>& attr_locDA = node_ptr->attr_location();

	for(U32 i = 0; i < attr_locDA.size(); ++i)
	{
		S32 attr_loc= StreamData::get_attribute_index((VertexAttributeType)attr_locDA[i]._vertex_attribute_type);
		const char* attr_name = attr_locDA[i]._name.c_str();
		if(attr_loc != -1)
			glBindAttribLocation(shader_handle,attr_loc,attr_name);
	}
}

dPtr<ShaderComponentMetaNode> ShaderComponent::meta_ptr()
{
	return dPtr_CAST(ShaderComponentMetaNode,_metaPtr);
}

void ShaderComponent::attach_to_shader(const U32& handle)
{
	glAttachShader(handle,_component_handle);
}

}


