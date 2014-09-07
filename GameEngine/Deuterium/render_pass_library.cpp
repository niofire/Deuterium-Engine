#include "render_pass_library.h"

#include "3rdParty\rapidjson\stringbuffer.h"
#include "3rdParty\rapidjson\document.h"
#include "3rdParty\rapidjson\writer.h"
#include "3rdParty\rapidjson\error\en.h"
#include "json_parser.h"
#include "uniform_type_handler.h"
#include "render_target.h"""
namespace deuterium
{
	RenderPassLibrary::RenderPassLibrary()
	{
		
	}

	RenderPassLibrary::~RenderPassLibrary()
	{

	}

	bool RenderPassLibrary::load_render_assets(const std::string& render_asset_filename)
	{
		using namespace rapidjson;
		std::string json_str = JsonParser::get_json_from_file(render_asset_filename.c_str());
		Document json_render_asset_parser;
		if(!JsonParser::load_json_document(json_render_asset_parser,json_str))
			return false;

		//Check if json parser has member and its an array
		if(!JsonParser::has_member(json_render_asset_parser,"rendering_resources",render_asset_filename.c_str()))
			return false;

		const Value& json_rendering_resource_parser = json_render_asset_parser["rendering_resources"];

		this->load_rendering_resource(json_rendering_resource_parser, RenderingResource::SHADER_EXTENSION);
		this->load_rendering_resource(json_rendering_resource_parser, RenderingResource::SHADER_COMPONENT);
		this->load_rendering_resource(json_rendering_resource_parser, RenderingResource::SHADER_PASS);
		this->load_rendering_resource(json_rendering_resource_parser, RenderingResource::RENDER_TARGET);
		this->load_rendering_resource(json_rendering_resource_parser, RenderingResource::UNIFORM_BUFFER);
	}
	
	void RenderPassLibrary::link_render_assets(const std::string& render_pipe_filename)
	{
		this->_render_pass_DA.clear();
		
		std::vector<ShaderExtension> _shader_extensions_DA;
		std::vector<UniformBuffer>  _u_buffer_DA;
		std::vector<ShaderPass> _shader_pass_DA;
		std::vector<ShaderComponent> _shader_component_DA;
		std::vector<RenderTarget> _render_target_DA;

		//--------------------------------------
		//			Link the ShaderExtensions
		//--------------------------------------
		for (U32 i = 0; i < this->_rendering_resource_list.size(); ++i)
		{
			if (_rendering_resource_list[i]->type == RenderingResource::SHADER_EXTENSION)
			{
				dPtr<ShaderExtensionRenderingResource> ptr = dPtr_CAST(ShaderExtensionRenderingResource, _rendering_resource_list[i]);
				ShaderExtension ext;
				ext.set_name(ptr->name());
				ext.set_extension(ptr->source());

				_shader_extensions_DA.push_back(ext);
			}
		}


		//-----------------------------------
		//		Link the UniformBuffer
		//-----------------------------------
		for (U32 i = 0; i < this->_rendering_resource_list.size(); ++i)
		{
			if (_rendering_resource_list[i]->type == RenderingResource::UNIFORM_BUFFER)
			{
				dPtr<UniformBufferRenderingResource> ptr = dPtr_CAST(UniformBufferRenderingResource, _rendering_resource_list[i]);
				UniformBuffer u_buffer;
				u_buffer.set_name(ptr->name());
				const std::vector<UniformBufferRenderingResource::Uniform> uniform_raw_data_DA = ptr->uniform_DA();

				for (int j = 0; j < uniform_raw_data_DA.size(); ++j)
				{
					 DeuteriumUniformType type = UniformTypeHandler::to_enum(uniform_raw_data_DA[j].type());
					 if (type != DeuteriumUniformType::D_UNKNOWN_UNIFORM_TYPE)
					 {
						 u_buffer.add_uniform(type, uniform_raw_data_DA[j].name().c_str());
					 }
				}

			}
		}

		//------------------------------------------
		//		Link the RendeTargets
		//------------------------------------------
		for (U32 i = 0; i < this->_rendering_resource_list.size(); ++i)
		{
			if (_rendering_resource_list[i]->type() == RenderingResource::RENDER_TARGET)
			{
				dPtr<RenderTargetRenderingResource> ptr = dPtr_CAST(RenderTargetRenderingResource, _rendering_resource_list[i]);
				RenderTarget target;
				target.set_name(ptr->name());
				target.set_size(ptr->size());
				target.set_format(ptr->format());
				_render_target_DA.push_back(target);
			}
		}

		//------------------------------------------
		//		Link the ShaderComponents
		//------------------------------------------
		for(U32 i = 0; i < this->_rendering_resource_list.size(); ++i)
		{
			if(_rendering_resource_list[i]->type() == RenderingResource::SHADER_COMPONENT)
			{
				dPtr<ShaderComponentRenderingResource> ptr = dPtr_CAST(ShaderComponentRenderingResource, _rendering_resource_list[i]);
				ShaderComponent shader_component;
				shader_component.set_name(ptr->

			}
		}

	}

	void RenderPassLibrary::clear_render_assets()
	{
		this->_rendering_resource_list.clear();
	}

	void RenderPassLibrary::clear_library()
	{
		this->clear_render_assets();
	}

	dPtr<RenderPass> RenderPassLibrary::fetch_render_pass(U32 shader_pass_id)
	{
		if (shader_pass_id >= _render_pass_DA.size())
			return dPtr<RenderPass>();
		return this->_render_pass_DA[shader_pass_id];
	}

	dPtr<RenderPass> RenderPassLibrary::fetch_render_pass(const std::string& shader_pass_name)
	{
		return dPtr<RenderPass>();
	}

	void RenderPassLibrary::load_rendering_resource(const rapidjson::Value& json_rendering_resource_parser, RenderingResource::Type t)
	{
		using namespace rapidjson;
		const char* json_tag = RenderingResource::json_tag(t).c_str();
		if (json_rendering_resource_parser.HasMember(json_tag))
		{
			const Value& json_array_parser = json_rendering_resource_parser[json_tag];
			if (JsonParser::is_array(json_array_parser, json_tag, ""))
			{
				for (U32 i = 0; i < json_array_parser.Size(); ++i)
				{
					const Value& json_rendering_resource_instance_parser = json_array_parser[i];
					dPtr<RenderingResource> rr_ptr = RenderingResource::allocate_rendering_resource(t);
					if (rr_ptr.is_null())
						return;
					rr_ptr->load(json_rendering_resource_instance_parser);
					this->_rendering_resource_list.push_back(rr_ptr);
				}
			}
		}
	}
}