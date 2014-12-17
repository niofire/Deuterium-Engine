#include "rendering_resource.h"
#include "json_parser.h"
#include "stream_data.h"
#include "assets.h"

namespace deuterium
{
	
	const std::string& RenderingResource::json_tag(Type t)
	{
		switch (t)
		{
		case SHADER_EXTENSION:
			return "shader_extension";
		case SHADER_COMPONENT:
			return "shader";
		case SHADER_PASS:
			return "pass";
		case RENDER_TARGET:
			return "render_target";
		case UNIFORM_BUFFER:
			return "uniform_buffer";
		default:
			return "unknown rendering resource";
		}
		return "unknown rendering resource";
	}

	dPtr<RenderingResource> RenderingResource::allocate_rendering_resource(Type t)
	{
		switch (t)
		{
		case SHADER_EXTENSION:
			return dPtr<RenderingResource>(new ShaderExtensionRenderingResource);
		case SHADER_COMPONENT:
			return dPtr<RenderingResource>(new ShaderComponentRenderingResource);
		case SHADER_PASS:
			return dPtr<RenderingResource>(new ShaderPassRenderingResource);
		case RENDER_TARGET:
			return dPtr<RenderingResource>(new RenderTargetRenderingResource);
		case UNIFORM_BUFFER:
			return dPtr<RenderingResource>(new UniformBufferRenderingResource);
		default:
			return dPtr<RenderingResource>();
		}
		return dPtr<RenderingResource>();
	}

	//-------------------------------------------------------
	//		ShaderExtensionRenderingResource
	//-------------------------------------------------------
	ShaderExtensionRenderingResource::ShaderExtensionRenderingResource() : RenderingResource()
	{
		this->_type		= SHADER_EXTENSION; 
	}

	dPtr<ShaderExtension> ShaderExtensionRenderingResource::link()
	{
		dPtr<ShaderExtension> ptr = dPtr<ShaderExtension>(new ShaderExtension);
		if(!_is_loaded)
			return ptr;
		ptr->set_name(this->_name);
		ptr->set_extension(this->_source);

		return ptr;
	}

	bool ShaderExtensionRenderingResource::load(const rapidjson::Value& json_shader_extension_parser)
	{
		using namespace rapidjson;
		
		if(!JsonParser::fetch_string(json_shader_extension_parser,_name,"name",_filename.c_str()))
			return false;

		//fetch the extension source
		if(!JsonParser::has_member(json_shader_extension_parser,"source",this->_filename.c_str())
			|| !JsonParser::is_array(json_shader_extension_parser,"source",this->_filename.c_str()))
			return false;
		const Value& json_shader_extension_src = json_shader_extension_parser["source"];
		this->_source = "";

		for(U32 i = 0; i < json_shader_extension_src.Size(); ++i)
		{
			this->_source += json_shader_extension_src[i].GetString();
		}
		_is_loaded = true;
		return true;
	}

	//-------------------------------------------------------
	//		ShaderComponentRenderingResource
	//-------------------------------------------------------
	ShaderComponentRenderingResource::ShaderComponentRenderingResource() : RenderingResource()
	{
		this->_type		= SHADER_COMPONENT; 
	}

	dPtr<ShaderComponent> ShaderComponentRenderingResource::link(Assets<ShaderExtension>& shader_extension_assets, 
		Assets<UniformBuffer>& uniform_buffer_assets)
	{
		dPtr<ShaderComponent> shader = dPtr<ShaderComponent>(new ShaderComponent());
		dPtr<UniformBuffer> dynamic_buffer = this->_dynamic_u_buffer.link();
		shader->set_dynamic_uniform_buffer(dynamic_buffer);
		
		//Load in extensions
		for(int i = 0; i < this->_extension_name_DA.size(); ++i)
		{
			dPtr<ShaderExtension> ext_ptr = shader_extension_assets.get_asset(_extension_name_DA[i]);
			if(!ext_ptr.is_null())
				shader->add_shader_extension(ext_ptr);
		}

		//Load in constant uniform buffers
		for(int i = 0; i < this->_u_buffer_name_DA.size() ;++i)
		{
			dPtr<UniformBuffer> u_buffer_ptr = uniform_buffer_assets.get_asset(_u_buffer_name_DA[i]);
			if(!u_buffer_ptr.is_null())
				shader->add_constant_uniform_buffer(u_buffer_ptr);
		}

		//name
		shader->set_name(this->_name);

		//source
		std::string src = "";
		for(int i = 0;i < _shader_src.size(); ++i)
			src += _shader_src[i];
		shader->set_source(src);

		//type
		if(StringHelper::is_identical_string(this->_shader_type,"fragment"))
			shader->set_type(GL_FRAGMENT_SHADER);
		else if(StringHelper::is_identical_string(this->_shader_type, "vertex"))
			shader->set_type(GL_VERTEX_SHADER);
		else
			return dPtr<ShaderComponent>();

		//Attribute locations
		if(shader->type() == GL_VERTEX_SHADER)
		{

		}
	}

	bool ShaderComponentRenderingResource::load(const rapidjson::Value& json_shader_component_parser)
	{
		using namespace rapidjson;
	

		if(!JsonParser::fetch_string(json_shader_component_parser,_name,"name",_filename.c_str()))
			return false;

		//Fetch the shader extension names. These will be loaded in after all data has been cached in the render_pass_library
		JsonParser::fetch_string_DA(json_shader_component_parser,this->_extension_name_DA,"extension",_filename.c_str());
		
		JsonParser::fetch_string_DA(json_shader_component_parser,this->_u_buffer_name_DA,"include_ubuffer",_filename.c_str());

		if(!JsonParser::fetch_string(json_shader_component_parser,this->_shader_type,"type",_filename.c_str()))
			return false;
		
		if(!JsonParser::has_member(json_shader_component_parser,"ubuffer",_filename.c_str()))
			return false;
		this->_dynamic_u_buffer.load(json_shader_component_parser["ubuffer"]);


		//Load shader attribute
		if(JsonParser::has_member(json_shader_component_parser,"attribute",_filename.c_str()))
		{
			const Value& json_attr_parser = json_shader_component_parser["attribute"];
			for(int i = 1; i < StreamType::NULL0; i = i << 1)
			{
				std::string stream_type_str = StreamData::to_string((StreamType)i);
				if(json_attr_parser.HasMember("attribute"))
				{
					this->_attribute_DA.push_back(Attribute(stream_type_str,json_attr_parser[stream_type_str.c_str()].GetString()));
				}
			}
		}
		
		if(!JsonParser::fetch_string_DA(json_shader_component_parser,_shader_src,"source",_filename.c_str()))
			return false;		
		return true;
	}

	//-------------------------------------------------------
	//		ShaderPassRenderingResource
	//-------------------------------------------------------
	ShaderPassRenderingResource::ShaderPassRenderingResource() : RenderingResource()
	{
		this->_type		= SHADER_PASS; 
	}

	dPtr<ShaderPass> ShaderPassRenderingResource::link(Assets<ShaderComponent >& shader_component_assets)
	{
		dPtr<ShaderComponent> vertex_shader = shader_component_assets.get_asset(this->_vertex_name);
		dPtr<ShaderComponent> fragment_shader = shader_component_assets.get_asset(this->_fragment_name);
		if(vertex_shader.is_null() || fragment_shader.is_null() || !this->_is_loaded)
			return dPtr<ShaderPass>();

		dPtr<ShaderPass> ptr = dPtr<ShaderPass>(new ShaderPass(vertex_shader.value(), fragment_shader.value()));
		ptr->set_name(this->_name);
		return ptr;
	}

	bool ShaderPassRenderingResource::load(const rapidjson::Value& json_shader_pass_parser)
	{
		using namespace rapidjson;

		if(!JsonParser::fetch_string(json_shader_pass_parser,this->_name,"name",_filename.c_str()))
			return false;

		if(!JsonParser::fetch_string(json_shader_pass_parser,this->_vertex_name,"vertex",_filename.c_str()))
			return false;

		if(!JsonParser::fetch_string(json_shader_pass_parser,this->_fragment_name,"fragment",_filename.c_str()))
			return false;
		this->_is_loaded = true;
		return true;
	}


	//-------------------------------------------------------
	//		UniformBufferRenderingResource
	//-------------------------------------------------------
	UniformBufferRenderingResource::UniformBufferRenderingResource() : RenderingResource()
	{
		this->_type		= UNIFORM_BUFFER; 
	}

	dPtr<UniformBuffer> UniformBufferRenderingResource::link()
	{
		dPtr<UniformBuffer> ptr = dPtr<UniformBuffer>(new UniformBuffer);
		
		if(!this->_is_loaded)
			return ptr;
		ptr->set_name(this->_name);
		
		for(int i = 0; i < this->_uniform_DA.size(); ++i)
		{
			DeuteriumUniformType type = UniformTypeHandler::to_enum( this->_uniform_DA[i].type());
			if( type != DeuteriumUniformType::D_UNKNOWN_UNIFORM_TYPE)
			{
				ptr->add_uniform(type, this->_uniform_DA[i].name().c_str());
			}
		}
		return ptr;
	}

	bool UniformBufferRenderingResource::load(const rapidjson::Value& json_ubuffer_parser)
	{
		using namespace rapidjson;

		JsonParser::fetch_string(json_ubuffer_parser,this->_name,"name",_filename.c_str());
		
		for(U32 k = 0; k < UniformTypeHandler::num_of_uniform_types(); ++k)
		{
			std::string type_name = UniformTypeHandler::to_string((DeuteriumUniformType)k);

			//check if uniform buffer has the type
			if(json_ubuffer_parser.HasMember(type_name.c_str()))
			{
				//Get all of the uniform names for this particular type
				const Value& json_uniform_type = json_ubuffer_parser[type_name.c_str()];
				if(!JsonParser::is_array(json_uniform_type,type_name.c_str(),_filename.c_str()))
					return false;

				for(U32 j = 0 ;j < json_uniform_type.Size(); ++j)
				{
					if(!JsonParser::is_string(json_uniform_type[j],type_name.c_str(),_filename.c_str()))
						return false;
					this->_uniform_DA.push_back(Uniform(type_name,json_uniform_type[j].GetString()));
				}
			}
		}
		this->_is_loaded = true;
		return true;
		
	}

	//-------------------------------------------------------
	//		RenderTargetRenderingResource
	//-------------------------------------------------------
	RenderTargetRenderingResource::RenderTargetRenderingResource() : RenderingResource()
	{
		this->_type		= RENDER_TARGET; 
	}
	
	dPtr<RenderTarget> RenderTargetRenderingResource::link()
	{
		dPtr<RenderTarget> ptr = dPtr<RenderTarget>(new RenderTarget);
		if(!this->_is_loaded)
			return ptr;
		ptr->set_name(this->_name);
		ptr->set_size(this->_size);

		//TODO
		// Support additional render target formats
		if(StringHelper::is_identical_string("RGBA8", this->_format))
			ptr->set_format(GL_RGBA8);
		else if(StringHelper::is_identical_string("RGBA16F", this->_format))
			ptr->set_format(GL_RGBA16F);
		else
			ptr->set_format(GL_RGBA);

		return ptr;
	}

	bool RenderTargetRenderingResource::load(const rapidjson::Value& json_rt_parser)
	{
		using namespace rapidjson;
		
		if(!JsonParser::fetch_string(json_rt_parser,this->_name,"name",_filename.c_str()))
			return false;
		
		
		if (!json_rt_parser.HasMember("width") || !json_rt_parser.HasMember("height"))
		{
			D_ERROR("Render Target with name \"" + _name + "does not have any width or height.");
			return false;
		}
		if (!json_rt_parser["width"].IsNumber() || !json_rt_parser["height"].IsNumber())
		{
			D_ERROR("Render Target with name \"" + _name + "does not have a valid width or height.");
		}
		this->_size = Vec2f(json_rt_parser["width"].GetDouble(), json_rt_parser["height"].GetDouble());


		if (!JsonParser::fetch_string(json_rt_parser, this->_format, "format", _filename.c_str()))
			return false;
		this->_is_loaded = true;
		return true;
	}


}