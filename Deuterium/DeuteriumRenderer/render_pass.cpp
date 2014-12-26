#include "render_pass.h"

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
					//Bind the given shader parameters to the shaderpass
					_draw_requestDA[j]->
				}
			}

			//Cleanup..
			p.end_pass();

		}
	}



}