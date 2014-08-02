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
		JSON_HAS_MEMBER(json_shader_data,"shader",shader_data_filename)
			const Value& shaders = json_shader_data["shader"];
		JSON_IS_ARRAY(shaders,"shader",shader_data_filename);

		//cycle through all shader data
		for(U32 i = 0; i < shaders.Size(); ++i)
		{
			d_ptr<ShaderComponent> component(new ShaderComponent);
			//---------------------------------------------
			//				Shader Name
			//---------------------------------------------
			JSON_HAS_MEMBER(shaders[i],"name",shader_data_filename)
				const Value& json_shader_name = shaders[i]["name"];
			JSON_IS_STRING(json_shader_name,"name",shader_data_filename);
			component->set_name(std::string(json_shader_name.GetString()));


			//---------------------------------------------
			//				Shader Extension Includes
			//---------------------------------------------
			const char* include_source_str = "include_source";
			JSON_HAS_MEMBER(shaders[i],include_source_str,shader_data_filename)
				const Value& json_include_array = shaders[i][include_source_str];
			JSON_IS_ARRAY(json_include_array, include_source_str,shader_data_filename)

			for(U32 j = 0; j < json_include_array.Size(); ++j)
			{
				JSON_IS_STRING(json_include_array[j],include_source_str, shader_data_filename)
				std::string shader_extension_name = json_include_array[j].GetString();
				d_ptr<ShaderExtension> ext = this->_rendering_resources._shader_extension_assets.get_asset(shader_extension_name);
				if(!ext.is_null())
					component->add_source_extension(ext);
			}

			//---------------------------------------------
			//				Uniform Buffer Includes
			//---------------------------------------------
			const char* include_ubuffer_str = "include_ubuffer";
			if(shaders[i].HasMember(include_ubuffer_str))
			{
					const Value& json_include_ubuffer_array = shaders[i][include_ubuffer_str];
				JSON_IS_ARRAY(json_include_ubuffer_array, include_ubuffer_str,shader_data_filename)

				for(U32 j = 0; j < json_include_ubuffer_array.Size(); ++j)
				{
					JSON_IS_STRING(json_include_ubuffer_array[j],include_ubuffer_str, shader_data_filename)
					std::string shader_extension_name = json_include_ubuffer_array[j].GetString();
					d_ptr<UniformBuffer> ubuffer_ext = this->_rendering_resources._uniform_buffer_assets.get_asset(shader_extension_name);
					if(!ubuffer_ext.is_null())
						component->add_constant_uniform_buffer(ubuffer_ext);
				}
			}

			//---------------------------------------------
			//				Shader Type
			//---------------------------------------------
			const char* type_str = "type";
			JSON_HAS_MEMBER(shaders[i],type_str,shader_data_filename);
			const Value& json_shader_type = shaders[i][type_str];
			JSON_IS_STRING(json_shader_type,type_str,shader_data_filename);

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
				D_ERROR("In file " + std::string(shader_data_filename) + " in shader named " + component->name() + ": No type valid type entered");
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
				JSON_HAS_MEMBER(shaders[i],attribute_str,shader_data_filename);
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
			JSON_HAS_MEMBER(shaders[i],"source",shader_data_filename);
			const Value& json_shader_source = shaders[i]["source"];
			JSON_IS_STRING(json_shader_source,"source",shader_data_filename);
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
			JSON_IS_ARRAY(json_pass_array,"pass",shader_data_filename);
			for(int i = 0; i  < json_pass_array.Size(); ++i)
			{
				
				const Value& json_pass = json_pass_array[i];
				
				JSON_HAS_MEMBER(json_pass,"fragment",shader_data_filename);
				const Value& json_pass_fragment_name = json_pass["fragment"];
				JSON_IS_STRING(json_pass_fragment_name,"fragment",shader_data_filename);
				
				JSON_HAS_MEMBER(json_pass,"vertex",shader_data_filename);
				const Value& json_pass_vertex_name = json_pass["vertex"];
				JSON_IS_STRING(json_pass_vertex_name,"vertex",shader_data_filename);


				d_ptr<ShaderComponent> fragment_shader = _rendering_resources._shader_component_assets.get_asset(json_pass_fragment_name.GetString());
				d_ptr<ShaderComponent> vertex_shader = _rendering_resources._shader_component_assets.get_asset(json_pass_vertex_name.GetString());
				if(fragment_shader.is_null() || vertex_shader.is_null())
					return false;
				d_ptr<ShaderPass> pass(new ShaderPass(vertex_shader.value(),fragment_shader.value()));

				
				
				JSON_HAS_MEMBER(json_pass,"name",shader_data_filename);
				const Value& json_pass_name = json_pass["name"];
				JSON_IS_STRING(json_pass_name,"name",shader_data_filename);
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
		
		JSON_HAS_MEMBER(json_parser,"shader_extension",filename);
		const Value& json_shader_ext = json_parser["shader_extension"];

		JSON_IS_ARRAY(json_shader_ext,"shader_extension",filename);

		for(int i = 0; i < json_shader_ext.Size(); ++i)
		{
			d_ptr<ShaderExtension> ext(new ShaderExtension);

			//Fetch extension name
			JSON_HAS_MEMBER(json_shader_ext[i],"name",filename);
			const Value& json_ext_name = json_shader_ext[i]["name"];
			JSON_IS_STRING(json_ext_name,"name",filename);
			ext->set_name(json_ext_name.GetString());

			//Fetch extension source
			JSON_HAS_MEMBER(json_shader_ext[i],"source",filename);
			const Value& json_ext_source = json_shader_ext[i]["source"];
			JSON_IS_STRING(json_ext_source,"source",filename);
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
		JSON_HAS_MEMBER(parser,"rendering_resources", filename);


		//--------------------------------------------
		//		Predefined Uniform Buffer
		//--------------------------------------------
		const Value& json_rendering_resources = parser["rendering_resources"];
		//Predefined Uniform Buffer parsed here
		if(json_rendering_resources.HasMember("uniform_buffer"))
		{
			const Value& json_uniform_buffer_array = json_rendering_resources["uniform_buffer"];
			JSON_IS_ARRAY(json_uniform_buffer_array,"uniform_buffer",filename);

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
		JSON_HAS_MEMBER(parser,"shader_assets",filename);

		const Value& json_render_assets_package = parser["shader_assets"];

		//---------------------------------------------
		//		Absolute file paths
		//---------------------------------------------
		std::vector<std::string> abs_filepaths_DA;

		if(json_render_assets_package.HasMember("absolute"))
		{
			const Value& json_absolute_filepaths = json_render_assets_package["absolute"];
			JSON_IS_ARRAY(json_absolute_filepaths,"absolute",filename);

			for(U32 i = 0; i < json_absolute_filepaths.Size(); ++i)
			{
				const Value& json_abs_filepath = json_absolute_filepaths[i];
				JSON_IS_STRING(json_abs_filepath,"absolute",filename);
				abs_filepaths_DA.push_back(json_abs_filepath.GetString());
			}
		}

		for(U32 i = 0 ; i < abs_filepaths_DA.size(); ++i)
		{
			std::string filepath = abs_filepaths_DA[i];
			if(filepath.find(".shader_data") != std::string::npos)
			{
				if(!this->load_shader_data(filepath.c_str())) {
					D_ERROR("In the render_assets_package_file: " + std::string(filename) + ": The file " + filepath + " did not load properly.");
				}
			}
			else if(filepath.find(".shader_extension") != std::string::npos)
			{
				if(!this->load_shader_extension(filepath.c_str())) {
					D_ERROR("In the render_assets_package_file: " + std::string(filename) + ": The file " + filepath + " did not load properly.");
				}
			}
			else {
				D_ERROR("In the render_assets_package file: " + std::string(filename) + ": Filepath " + filepath + " is not supported.");
			}
		}


		//-------------------------------------------------------
		//		Relative file paths
		//-------------------------------------------------------
		std::vector<std::string> rel_filepaths_DA;

		if(json_render_assets_package.HasMember("relative"))
		{
			const Value& json_relative_filepaths = json_render_assets_package["relative"];
			JSON_IS_ARRAY(json_relative_filepaths,"relative",filename);
			for(U32 i = 0; i < json_relative_filepaths.Size(); ++i)
			{
				const Value& json_rel_filepath = json_relative_filepaths[i];
				JSON_IS_STRING(json_rel_filepath,"relative",filename);
				rel_filepaths_DA.push_back(json_rel_filepath.GetString());
			}
		}

		for(U32 i = 0 ; i < rel_filepaths_DA.size(); ++i)
		{
			std::string filepath = rel_filepaths_DA[i];
			if(filepath.find(".shader_data") != std::string::npos)
			{
				if(!this->load_shader_data(filepath.c_str())) {
					D_ERROR("In the render_assets_package_file: " + std::string(filename) + ": The file " + filepath + " did not load properly.");
				}
			}
			else if(filepath.find(".shader_extension") != std::string::npos) {
				if(!this->load_shader_extension(filepath.c_str())) {
					D_ERROR("In the render_assets_package_file: " + std::string(filename) + ": The file " + filepath + " did not load properly.");
				}
			}
			else {
				D_ERROR("In the render_assets_package file: " + std::string(filename) + ": Filepath " + filepath + " not supported.");
			}
		}

		return true;
	}

	bool ResourceLoader::load_uniform_buffer(const rapidjson::Value& json_element, const char* filename, const char* ubuffer_name)
	{
		using namespace rapidjson;
		d_ptr<UniformBuffer> u_buffer(new UniformBuffer);
		u_buffer->set_name(ubuffer_name);
		for(U32 k = 0; k < UniformTypeHandler::num_of_uniform_types(); ++k)
		{
			std::string type_name = UniformTypeHandler::to_string((DeuteriumUniformType)k);

			//check if uniform buffer has the type
			if(json_element.HasMember(type_name.c_str()))
			{
				//Get all of the uniform names for this particular type
				const Value& json_uniform_type = json_element[type_name.c_str()];
				JSON_IS_ARRAY(json_uniform_type,type_name, filename)
					for(U32 j = 0 ;j < json_uniform_type.Size(); ++j)
					{
						JSON_IS_STRING(json_uniform_type[j],type_name,filename);
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
		JSON_HAS_MEMBER(json_element,"name",filename);
		JSON_IS_STRING(json_element["name"],"name",filename);

		return load_uniform_buffer(json_element,filename,json_element["name"].GetString());
		
	}

	bool ResourceLoader::load_render_targets(const rapidjson::Value& json_element)
	{
		return true;
	}

}