#pragma once

#include <vector>
#include "shader_parameter.h"
#include "stream_data.h"
#include "IAsset.h"

namespace deuterium
{
	class AssetMeta;
class ShaderComponent : public IAsset
{

public:
	ShaderComponent();
	~ShaderComponent(void);

	//-------------------------------------------------
	//				Initialization Functions
	//-------------------------------------------------

	void attach_to_shader(const U32& handle);
	void compile(U32 id);
	//-------------------------------------------------
	//				Accessor / Mutators
	//-------------------------------------------------
	//Name of the shader, is unique.
	const	std::string& name();
	
	//Shader type, either GL_VERTEX or GL_FRAGMENT
	U32		type();

	//The ShaderComponent rendering handle
	const	 U32 handle() const {return _component_handle;}
	
	//-------------------------------------------------
	//				Shader Handling function
	//-------------------------------------------------
	void bind_shader_attribute(U32 shader_handle);

private:
	dPtr<ShaderComponentMetaNode> meta_ptr();
	bool	_is_compiled;
	U32	_component_handle;

};
}
