#pragma once
#include "d_typedef.h"
#include "deuterium_math.h"
namespace deuterium
{
	struct DrawRequest
	{
		DrawRequest(U32 render_pass_id, U32 mesh_handle, U32 material_handle, Mat4x4& transform) : _transform(transform)
		{
			_render_pass_id = render_pass_id;
			_mesh_handle = mesh_handle;
			_material_handle = material_handle;
		}
	public:

		U32 _render_pass_id;
		U32	_mesh_handle;
		U32 _material_handle;
		Mat4x4& _transform;
		ShaderPass::PassType _type;
	};
}
