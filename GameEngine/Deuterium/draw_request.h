#pragma once
#include "global_data.h"
#include "shader_pass.h"
#include "scene_object.h"

namespace deuterium
{

	struct DrawRequest
	{
		U32  _render_pass_id;
		dPtr<SceneObject> _obj; //contains mesh data, 
	};
}