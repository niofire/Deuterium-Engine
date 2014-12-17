#include "resource_loader.h"
#include "stream_data.h"

namespace deuterium
{
	ResourceLoader::ResourceLoader(void)
	{
	}


	ResourceLoader::~ResourceLoader(void)
	{
	}

	bool ResourceLoader::load_shader_data(const char* shader_data_filename)
	{
		using namespace rapidjson;

		std::string json_string = JsonParser::get_json_from_file(shader_data_filename);
		Document json_shader_data;
		if(!JsonParser::load_json_document(json_shader_data,json_string))
			return false;
		/////////////////////////////////////////////////////////////////
		//--------------------------------------------------------------
		//			Shader Components
		//--------------------------------------------------------------
		////////////////////////////////////////////////////////////////

		if(!JsonParser::has_member(json_shader_data,"shader",shader_data_filename))
			return false;
		const Value& shaders = json_shader_data["shader"];

		if(!JsonParser::is_array(shaders,"shader",shader_data_filename))
			return false;

		//cycle through all shader data
		for(U32 i = 0; i < shaders.Size(); ++i)
		{
			dPtr<ShaderComponent> component(new ShaderComponent);
			//---------------------------------------------
			//				Shader Name
			//---------------------------------------------
			if(!JsonParser::has_member(shaders[i],"name",shader_data_filename))
				return false;
			const Value& json_shader_name = shaders[i]["name"];
			if(!JsonParser::is_string(json_shader_name,"name",shader_data_filename))
				return false;
			component->set_name(std::string(json_shader_name.GetString()));


			//---------------------------------------------
			//				Shader Extension Includes
			//---------------------------------------------
			const char* include_source_str = "include_source";
			if(!JsonParser::has_member(shaders[i],include_source_str,shader_data_filename))
				return false;
			const Value& json_include_array = shaders[i][include_source_str];
			if(!JsonParser::is_array(json_include_array,include_source_str,shader_data_filename))
				return false;


			for(U32 j = 0; j < json_include_array.Size(); ++j)
			{
				if(!JsonParser::is_string(json_include_array[j],include_source_str,shader_data_filename))
					return false;

				std::string shader_extension_name = json_include_array[j].GetString();
				dPtr<ShaderExtension> ext = _rendering_resources._shader_extension_assets.get_asset(shader_extension_name);
				if(!ext.is_null())
					component->add_extension_source(ext);
			}

			//---------------------------------------------
			//				Uniform Buffer Includes
			//---------------------------------------------
			const char* include_ubuffer_str = "include_ubuffer";
			if(shaders[i].HasMember(include_ubuffer_str))
			{
				const Value& json_include_ubuffer_array = shaders[i][include_ubuffer_str];
				if(!JsonParser::is_array(json_include_ubuffer_array,include_ubuffer_str,shader_data_filename))
					return false;


				for(U32 j = 0; j < json_include_ubuffer_array.Size(); ++j)
				{
					if(!JsonParser::is_string(json_include_ubuffer_array[j],include_ubuffer_str,shader_data_filename))
						return false;
					std::string shader_extension_name = json_include_ubuffer_array[j].GetString();
					dPtr<UniformBuffer> ubuffer_ext = _rendering_resources._uniform_buffer_assets.get_asset(shader_extension_name);
					if(!ubuffer_ext.is_null())
						component->add_constant_uniform_buffer(ubuffer_ext);
				}
			}

			//---------------------------------------------
			//				Shader Type
			//---------------------------------------------
			const char* type_str = "type";
			if(!JsonParser::has_member(shaders[i],type_str,shader_data_filename))
				return false;
			const Value& json_shader_type = shaders[i][type_str];
			if(!JsonParser::is_string(json_shader_type,type_str,shader_data_filename))
				return false;

			std::string type = json_shader_type.GetString();

			if(type.find("vertex") != std::string::npos && type.find("fragment") == std::string::npos)
			{
				component->set_type(GL_VERTEX_SHADER);
			}
			else if(type.find("fragment") != std::string::npos && type.find("vertex") == std::string::npos)
			{
				component->set_type(GL_FRAGMENT_SHADER);
			}
			else
			{
				//D_ERROR("In file " + shader_data_filename) + " in shader named " + component->name() + ": No type valid type entered");
				return false;
			}


			//---------------------------------------------
			//				Shader Uniform Buffer
			//---------------------------------------------	
			const char* uniform_buffer_str = "ubuffer";
			if(shaders[i].HasMember(uniform_buffer_str))
			{
				const Value& json_ubuffer = shaders[i][uniform_buffer_str];
				if(json_ubuffer.IsArray())
				{
					D_ERROR("Only one uniform buffer can be declared dynamically");

				}
				else
				{
					if(!this->load_uniform_buffer(json_ubuffer,shader_data_filename,(component->name() +"_ubuffer").c_str()))
						return false;
					component->set_dynamic_uniform_buffer(_rendering_resources._uniform_buffer_assets.get_asset((component->name() +"_ubuffer").c_str()));
				}
			}

			//---------------------------------------------
			//				Shader Attribute (Vertex Shader Only)
			//---------------------------------------------
			if(component->type() == GL_VERTEX_SHADER)
			{
				const char* attribute_str = "attribute";
				if(!JsonParser::has_member(shaders[i],attribute_str,shader_data_filename))
					return false;
				const Value& json_attrib = shaders[i][attribute_str];
				for(int i = 1; i < StreamType::NULL0; i = i << 1)
				{
					std::string stream_type_str = StreamData::to_string((StreamType)i);
					if(json_attrib.HasMember(stream_type_str.c_str()))
					{
						component->add_attribute_location((StreamType)i,json_attrib[stream_type_str.c_str()].GetString());
					}
				}
			}

			//---------------------------------------------
			//				Shader Source
			//---------------------------------------------
			if(!JsonParser::has_member(shaders[i],"source",shader_data_filename))
				return false;
			const Value& json_shader_source = shaders[i]["source"];
			if(!JsonParser::is_string(json_shader_source,"source",shader_data_filename))
				return false;
			component->set_source(json_shader_source.GetString());
			if(!_rendering_resources._shader_component_assets.exists(component->name().c_str()))
			{
				U32 id;
				this->_rendering_resources._shader_component_assets.add_asset(id,component,component->name());
			}

		}
		/////////////////////////////////////////////////////////////////
		//--------------------------------------------------------------
		//			Shader Pass
		//--------------------------------------------------------------
		////////////////////////////////////////////////////////////////
		//This section basically loads Shader Components into the predefined shader passes, 
		//
		if(json_shader_data.HasMember("pass"))
		{
			const Value& json_pass_array = json_shader_data["pass"];
			if(!JsonParser::is_array(json_pass_array,"pass",shader_data_filename))
				return false;
			for(int i = 0; i  < json_pass_array.Size(); ++i)
			{

				const Value& json_pass = json_pass_array[i];

				if(!JsonParser::has_member(json_pass,"fragment",shader_data_filename))
					return false;
				const Value& json_pass_fragment_name = json_pass["fragment"];
				if(!JsonParser::is_string(json_pass_fragment_name,"fragment",shader_data_filename))
					return false;

				if(!JsonParser::has_member(json_pass,"vertex",shader_data_filename))
					return false;
				const Value& json_pass_vertex_name = json_pass["vertex"];
				if(!JsonParser::is_string(json_pass_vertex_name,"vertex",shader_data_filename))
					return false;



				dPtr<ShaderComponent> fragment_shader = _rendering_resources._shader_component_assets.get_asset(json_pass_fragment_name.GetString());
				dPtr<ShaderComponent> vertex_shader = _rendering_resources._shader_component_assets.get_asset(json_pass_vertex_name.GetString());
				if(fragment_shader.is_null() || vertex_shader.is_null())
					return false;
				dPtr<ShaderPass> pass(new ShaderPass(vertex_shader.value(),fragment_shader.value()));



				if(!JsonParser::has_member(json_pass,"name",shader_data_filename))
					return false;
				const Value& json_pass_name = json_pass["name"];
				if(!JsonParser::is_string(json_pass_name,"name",shader_data_filename))
					return false;
				pass->set_name(json_pass_name.GetString());
				U32 id;
				this->_rendering_resources._shader_pass_assets.add_asset(id,pass,pass->name().c_str());
			}
		}

		return true;

	}
	bool ResourceLoader::load_shader_extension(const char* filename)
	{
		using namespace rapidjson;
		std::string json_ext_str = JsonParser::get_json_from_file(filename);
		Document json_parser;
		if(!JsonParser::load_json_document(json_parser,json_ext_str))
		{
			return false;
		}

		if(!JsonParser::has_member(json_parser,"shader_extension",filename))
			return false;
		const Value& json_shader_ext = json_parser["shader_extension"];

		if(!JsonParser::is_array(json_shader_ext,"shader_extension",filename))
			return false;

		for(int i = 0; i < json_shader_ext.Size(); ++i)
		{
			dPtr<ShaderExtension> ext(new ShaderExtension);

			//Fetch extension name
			if(!JsonParser::has_member(json_shader_ext[i],"name",filename))
				return false;
			const Value& json_ext_name = json_shader_ext[i]["name"];
			if(!JsonParser::is_string(json_ext_name,"name",filename))
				return false;
			ext->set_name(json_ext_name.GetString());

			//Fetch extension source
			if(!JsonParser::has_member(json_shader_ext[i],"source",filename))
				return false;
			const Value& json_ext_source = json_shader_ext[i]["source"];
			if(!JsonParser::is_string(json_ext_source,"source",filename))
				return false;

			ext->set_extension(json_ext_source.GetString());


			//add shader extension to assets if it does not exist
			if(!this->_rendering_resources._shader_extension_assets.exists(ext->name().c_str()))
			{
				U32 id;
				this->_rendering_resources._shader_extension_assets.add_asset(id,ext,ext->name());
			}

		}
		return true;
	}


	bool ResourceLoader::load_render_assets(const char* filename)
	{
		using namespace rapidjson;
		std::string json_str = JsonParser::get_json_from_file(filename);
		Document parser;
		if(!JsonParser::load_json_document(parser,json_str))
			return false;

		////////////////////////////////////////////////////////
		//			
		//			Resources
		//
		////////////////////////////////////////////////////////
		if(!JsonParser::has_member(parser,"rendering_resources",filename))
			return false;
		const Value& json_rendering_resources = parser["rendering_resources"];


		//--------------------------------------------
		//		Render Targets
		//--------------------------------------------

		//Load in the back_buffer
		dPtr<RenderTarget> back_buffer_rt(new RenderTarget(true));
		U32 rt_id;
		_rendering_resources._render_target_assets.add_asset(rt_id,back_buffer_rt, back_buffer_rt->name());





		//--------------------------------------------
		//		Predefined Uniform Buffer
		//--------------------------------------------

		//Predefined Uniform Buffer parsed here
		if(json_rendering_resources.HasMember("uniform_buffer"))
		{
			const Value& json_uniform_buffer_array = json_rendering_resources["uniform_buffer"];
			if(!JsonParser::is_array(json_uniform_buffer_array,"uniform_buffer",filename))
				return false;


			for(U32 i = 0; i < json_uniform_buffer_array.Size(); ++i)
			{
				if(!this->load_uniform_buffer(json_uniform_buffer_array[i],filename))
					return false;
			}
		}

		////////////////////////////////////////////////////////
		//			
		//			Shader Assets
		//
		////////////////////////////////////////////////////////
		if(!JsonParser::has_member(parser,"shader_assets",filename))
			return false;


		const Value& json_render_assets_package = parser["shader_assets"];

		//---------------------------------------------
		//		include file paths
		//---------------------------------------------
		std::vector<std::string> inc_filepaths_DA;
		const char* include_str = "include";
		if(json_render_assets_package.HasMember(include_str))
		{
			const Value& json_include_filepaths = json_render_assets_package[include_str];

			if(!JsonParser::is_array(json_include_filepaths,include_str,filename))
				return false;

			for(U32 i = 0; i < json_include_filepaths.Size(); ++i)
			{
				const Value& json_inc_filepath = json_include_filepaths[i];
				if(!JsonParser::is_string(json_inc_filepath,include_str,filename))
					return false;
				inc_filepaths_DA.push_back(json_inc_filepath.GetString());
			}
		}

		for(U32 i = 0 ; i < inc_filepaths_DA.size(); ++i)
		{
			std::string filepath = inc_filepaths_DA[i];
			if(filepath.find(".shader_data") != std::string::npos)
			{
				if(!this->load_shader_data(filepath.c_str())) {
					dErrorStack::get_instance().push(
						"In the render_assets_package_file: " + std::string(filename) + ": The file " + filepath + " did not load properly.");
				}
			}
			else if(filepath.find(".shader_extension") != std::string::npos)
			{
				if(!this->load_shader_extension(filepath.c_str())) {
					dErrorStack::get_instance().push(
						"In the render_assets_package_file: " + std::string(filename) + ": The file " + filepath + " did not load properly.");
				}
			}
			else {
				dErrorStack::get_instance().push(
					"In the render_assets_package file: " + std::string(filename) + ": Filepath " + filepath + " is not supported.");
			}
		}


		return true;
	}

	bool ResourceLoader::load_uniform_buffer(const rapidjson::Value& json_element, const char* filename, const char* ubuffer_name)
	{
		using namespace rapidjson;
		dPtr<UniformBuffer> u_buffer(new UniformBuffer);
		u_buffer->set_name(ubuffer_name);
		for(U32 k = 0; k < UniformTypeHandler::num_of_uniform_types(); ++k)
		{
			std::string type_name = UniformTypeHandler::to_string((DeuteriumUniformType)k);

			//check if uniform buffer has the type
			if(json_element.HasMember(type_name.c_str()))
			{
				//Get all of the uniform names for this particular type
				const Value& json_uniform_type = json_element[type_name.c_str()];
				if(!JsonParser::is_array(json_uniform_type,type_name.c_str(),filename))
					return false;

				for(U32 j = 0 ;j < json_uniform_type.Size(); ++j)
				{
					if(!JsonParser::is_string(json_uniform_type[j],type_name.c_str(),filename))
						return false;
					u_buffer->add_uniform((DeuteriumUniformType)k,json_uniform_type[j].GetString());
				}
			}
		}
		U32 id;
		this->_rendering_resources._uniform_buffer_assets.add_asset(id,u_buffer,u_buffer->name());
		return true;
	}
	bool ResourceLoader::load_uniform_buffer(const rapidjson::Value& json_element,const char* filename)
	{
		using namespace rapidjson;

		//Fetch name
		if(!JsonParser::has_member(json_element,"name",filename))
			return false;
		if(!JsonParser::is_string(json_element["name"],"name",filename))
			return false;

		return load_uniform_buffer(json_element,filename,json_element["name"].GetString());

	}

	bool ResourceLoader::load_render_targets(const rapidjson::Value& json_element)
	{
		return true;
	}

}