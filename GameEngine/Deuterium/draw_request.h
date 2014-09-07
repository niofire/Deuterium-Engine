#pragma once
#include "d_typedef.h"
#include "shader_pass.h"
#include "mesh.h"
#include "scene_object.h"
namespace deuterium
{
	struct DrawRequest
	{
		enum ShadingStage {
			G_BUFFER,
			DEFERRED,
			POST_PROCESS,
		};
		ShadingStage _stage;
		ShaderPass& _pass;
		Mesh& _mesh;
		bool _is_transparent;
		UniformBuffer& _buffer;
	};
}
