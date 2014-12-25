#pragma once
#include "shader_pass.h"
namespace deuterium
{
	class ShaderPass;
	class RenderTarget;
	class DrawRequest;

	class RenderPass
	{

	public:
		RenderPass();
		~RenderPass();

		//
		//
		//
	private:
		std::vector<dPtr<DrawRequest>> _draw_requestDA;
		std::vector<dPtr<ShaderPass>> _shaderPassDA;
	};


}