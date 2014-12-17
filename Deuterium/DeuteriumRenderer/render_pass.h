#pragma once
namespace deuterium
{
	class ShaderPass;
	class RenderTarget;
	class DrawRequest;
	struct RenderPass
	{
		/*	
		 *
		 */
		enum RenderPassType
		{
			MESH,
			POST_PROCESS,
			LIGHT,
			
		};
		
		RenderPassType _type;
		dPtr<ShaderPass> _pass;
		std::vector<dPtr<RenderTarget>> _input_rt_DA;
		std::vector<dPtr<RenderTarget>> _output_rt_DA;
		std::vector<dPtr<DrawRequest> > _draw_request_DA;
		
	};

}