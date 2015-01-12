#pragma once
#include "shader_pass.h"
#include "draw_request.h"
namespace deuterium
{

	class RenderPass 
		: public IAsset
	{

	public:
		RenderPass();
		~RenderPass();

		//-------------------------------------
		//			Instantiation Functions
		//-------------------------------------
		void		compile(U32 id);
		void		load_meta(const dPtr<MetaNode> node);

		//-------------------------------------
		//			Rendering Functions
		//-------------------------------------
		void				add_draw_request(dPtr<DrawRequest> d);
		void				render();

		//-------------------------------------
		//			Accessor / Mutators
		//-------------------------------------
		const std::string&	name() { return _name; }
		void				set_name(const std::string& name) { _name = name; }


	private:
		std::string _name;
		std::vector<dPtr<DrawRequest>> _draw_requestDA;
		std::vector<dPtr<ShaderPass>> _shaderPassDA;
	};


}