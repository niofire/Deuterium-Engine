#include "render_pipe.h"
#include <vector>
#include <fstream>
#include <string>
#include "uniform_buffer.h"
#include "string_helper.h"
#include "shader_parameter.h"
#include "resource_loader.h"
namespace deuterium
{
	RenderPipe::RenderPipe(void)
	{

	}


	RenderPipe::~RenderPipe(void)
	{

	}

	

	

	bool RenderPipe::load_render_pipe(const char* render_pipe_filename)
	{
		/*
		ResourceLoader loader;
		
		using namespace rapidjson;
		
		std::string json_str = JsonParser::get_json_from_file(render_pipe_filename);

		Document json_parser;
		if(!JsonParser::load_json_document(json_parser,json_str))
			return false;

		if(!JsonParser::has_member(json_parser,"rendering_assets",render_pipe_filename))
			return false;
		
		const Value& json_rendering_assets = json_parser["rendering_assets"];
		
		
		//---------------------------------------------
		//		include file paths
		//---------------------------------------------
		std::vector<std::string> inc_filepaths_DA;
		const char* include_str = "include";
		if(json_rendering_assets.HasMember(include_str))
		{
			const Value& json_include_filepaths = json_rendering_assets[include_str];
			
			if(!JsonParser::is_array(json_include_filepaths,include_str,render_pipe_filename))
				return false;

			for(U32 i = 0; i < json_include_filepaths.Size(); ++i)
			{
				const Value& json_inc_filepath = json_include_filepaths[i];
				if(!JsonParser::is_string(json_inc_filepath,include_str,render_pipe_filename))
					return false;
				inc_filepaths_DA.push_back(json_inc_filepath.GetString());
			}
		}

		for(U32 i = 0 ; i < inc_filepaths_DA.size(); ++i)
		{
			std::string filepath = inc_filepaths_DA[i];
			if(!loader.load_render_assets(filepath.c_str()))
				return false;
		}

		//-------------------------------------------
		//		Load the render passes
		//-------------------------------------------
			if(!JsonParser::has_member(json_parser,"render_pipe",render_pipe_filename))
			return false;
		const Value& json_render_pipe = json_parser["render_pipe"];

		//Iterate through each render pass type
		
		if(!JsonParser::has_member(json_render_pipe,"pass",render_pipe_filename))
			return false;
		const Value& json_pass = json_render_pipe["pass"];
		if(!JsonParser::is_array(json_pass,"pass",render_pipe_filename))
			return false;

		for(int i = 0; i < json_pass.Size(); ++i)
		{
			if(!JsonParser::has_member(json_pass[i],"name",render_pipe_filename)
				&& !JsonParser::has_member(json_pass[i],"input",render_pipe_filename)
				&& !JsonParser::has_member(json_pass[i],"output",render_pipe_filename))
			return false;

			RenderPass r_pass;
			dPtr<ShaderPass> shader_pass_ptr = ResourceLoader::s_rendering_resources._shader_pass_assets.get_asset(json_pass[i]["name"].GetString());
			
			if(shader_pass_ptr.is_null())
				continue;

			r_pass._pass = shader_pass_ptr;
			
			if(json_pass[i]["input"].IsArray())
			{
				for(int j = 0; j < json_pass[i]["input"].Size(); ++j)
				{
					std::string render_target_name = json_pass[i]["input"][j].GetString();
					dPtr<RenderTarget> target = loader.get_rendering_resouces()._render_target_assets.get_asset(render_target_name);
					if(!target.is_null())
						r_pass._input_rt_DA.push_back(target);
				}
			}
			else
			{
					std::string render_target_name = json_pass[i]["input"].GetString();
					dPtr<RenderTarget> target = loader.get_rendering_resouces()._render_target_assets.get_asset(render_target_name);
					if(!target.is_null())
						r_pass._input_rt_DA.push_back(target);
			}

			if(json_pass[i]["output"].IsArray())
			{
				for(int j = 0; j < json_pass[i]["output"].Size(); ++j)
				{
					std::string render_target_name = json_pass[i]["output"][j].GetString();
					dPtr<RenderTarget> target = loader.get_rendering_resouces()._render_target_assets.get_asset(render_target_name);
					if(!target.is_null())
						r_pass._output_rt_DA.push_back(target);
				}
			}
			else
			{
					std::string render_target_name = json_pass[i]["output"].GetString();
					dPtr<RenderTarget> target = loader.get_rendering_resouces()._render_target_assets.get_asset(render_target_name);
					if(!target.is_null())
						r_pass._output_rt_DA.push_back(target);
			}

			this->_render_pass_DA.push_back(r_pass);
		}
		*/
		return true;
	}

	bool RenderPipe::compile_render_pipe()
	{
		for(int i = 0 ; i < this->_render_pass_DA.size(); ++i)
		{
			if(!_render_pass_DA[i]._pass->compile_pass())
			{
				return false;
			}

		}
	}

	void RenderPipe::add_draw_request(dPtr<DrawRequest> req)
	{
		_render_pass_DA[req->_render_pass_id]._draw_request_DA.push_back(req);
	}


	void RenderPipe::flush_draw_request()
	{

	}

	const const std::string& RenderPipe::get_render_pass_name(U32 pass_id)
	{
		if(pass_id < _render_pass_DA.size())
		{
			return _render_pass_DA[pass_id]._pass->name();
		}
	}


}

render_pipe::render_pipe(void)
{
}


render_pipe::~render_pipe(void)
{
}
