#pragma once
#include "rendering_resource.h"
#include "d_ptr.h"
#include <string>
#include "3rdParty\rapidjson\document.h"
#include "d_typedef.h"
#include "shader_pass.h"
#include <vector>
namespace deuterium
{
	class RenderPassLibrary
	{
	public:
		static RenderPassLibrary& instance() {return s_render_pass_library;}
		
		dPtr<RenderPass> fetch_render_pass(const std::string& name);
		dPtr<RenderPass> fetch_render_pass(U32 id);

		//Link the currently held rendering resources into shaderpass'
		void						link_render_assets(const std::string& render_pipe_filename);
		
		//Load a .render_assets file into the library
		bool						load_render_assets(const std::string& render_assets_filename);

		//clears and frees the memory used by the RenderingResources
		void						clear_render_assets();

		//clears all of the shader passes and rendering resources stored in the library. Also frees the memory.
		void						clear_library();

	private:
		
		void load_rendering_resource(const rapidjson::Value& json_parser, RenderingResource::Type t);
		static RenderPassLibrary s_render_pass_library;
		RenderPassLibrary(void);
		~RenderPassLibrary(void);
		std::vector<dPtr<RenderingResource> > _rendering_resource_list;
		std::vector<dPtr<RenderPass> > _render_pass_DA;
	};
}
