#include "render_pass.h"
#include "rendering_assets_library.h"
namespace deuterium
{
	RenderPass::RenderPass()
	{

	}

	RenderPass::~RenderPass()
	{

	}


	//-------------------------------------
	//			Rendering Functions
	//-------------------------------------
	
	//Adds a draw request to this render pass.
	void RenderPass::add_draw_request(dPtr<DrawRequest> d)
	{
		_draw_requestDA.push_back(d);
	}

	void RenderPass::render()
	{
		for (int i = 0; i < _shaderPassDA.size(); ++i)
		{
			ShaderPass& p = _shaderPassDA[i].value();

			//Bind the shader and set the appropriate render states
			p.begin_pass();

			for (int j = 0; j < _draw_requestDA.size(); ++j)
			{
				if (p.type() == _draw_requestDA[j]->_type)
				{
					
					
					dPtr<RenderingAsset> ptr;
					ptr = RenderingAssetLibrary::instance().fetch_asset(RenderingAsset::MATERIAL,_draw_requestDA[j]->_material_handle);
					
					//The material pointer of this particular mesh
					dPtr<Material> matPtr = dPtr_CAST(Material,ptr);

					//Bind material to shader pass if it exists
					if(!matPtr.is_null())
						p.bind_material(matPtr.value());
					
					//bind mesh..


					//Set render settings..


					//Render!

				}
			}

			//Cleanup..
			p.end_pass();

		}
	}



}