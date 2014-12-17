#pragma once
#include "3rdParty\rapidjson\stringbuffer.h"
#include "3rdParty\rapidjson\document.h"
#include "3rdParty\rapidjson\writer.h"
#include "3rdParty\rapidjson\error\en.h"
#include "deuterium_math.h"
#include "uniform_buffer.h"
#include "shader_extension.h"
#include "uniform_buffer.h"
#include "shader_component.h"
#include "shader_pass.h"
#include "render_target.h"
namespace deuterium
{
	/*
	*	The RenderingResource class is an abstract class which allows to derive
	*	specialized RenderingResources (such as ShaderComponentRenderingResource).
	*
	*	The purpose of the RenderingResource and its derived classes is to cache data temporarily
	*	while all rendering resources are loaded from json files to the program.
	*	Since some structure have dependencies(ShaderComponent->ShaderExtension and ShaderPass-> ShaderComponent),
	*	these RenderingResources allows to defer the instanciation phase to 
	*	a time when all rendering related data has been cached in the program.
	*/
	class RenderingResource
	{
	public:
		enum Type 
		{
			SHADER_EXTENSION,
			SHADER_COMPONENT,
			SHADER_PASS,
			RENDER_TARGET,
			UNIFORM_BUFFER,
		};

		RenderingResource() { _is_loaded = false;}
		virtual ~RenderingResource();

		virtual bool load(const rapidjson::Value& json_rendering_resources) = 0;
		
		//returns the type of the rendering resource
		Type type() { return _type; }
		static const std::string& json_tag(Type t);
		static dPtr<RenderingResource> allocate_rendering_resource(Type t);

	protected:
		bool _is_loaded;
		std::string _filename;
		Type _type;
	};




	//-------------------------------------------------	
	//			ShaderExtensionRenderingResource class
	//-------------------------------------------------
	class ShaderExtensionRenderingResource : public RenderingResource
	{
	public:
		ShaderExtensionRenderingResource();
		~ShaderExtensionRenderingResource();
		
		bool load(const rapidjson::Value& json_rendering_resource);
		dPtr<ShaderExtension> link();
	private:
		std::string _name;
		std::string _source;
	};


	//-------------------------------------------------	
	//			ShaderPassRenderingResource class
	//-------------------------------------------------
	class ShaderPassRenderingResource : public RenderingResource
	{
	public:
		ShaderPassRenderingResource();
		~ShaderPassRenderingResource();
		
		bool load(const rapidjson::Value& json_rendering_resource);
		dPtr<ShaderPass> link(Assets<ShaderComponent>& shader_component_domain);
	private:
		std::string _name;
		std::string _fragment_name;
		std::string _vertex_name;
	};


	//-------------------------------------------------	
	//			UniformBufferRenderingResource class
	//-------------------------------------------------
	class UniformBufferRenderingResource : public RenderingResource
	{
	public:
		struct Uniform
		{
			Uniform(const std::string& type_str, const std::string& uniform_name)
			{
				_type_str = type_str;
				_name = uniform_name;
			}
			const std::string& type() const { return _type_str; }
			const std::string& name() const { return _name; }
		private:
			std::string _type_str;
			std::string _name;
		};
	public:
		UniformBufferRenderingResource();
		~UniformBufferRenderingResource();
		
		bool load(const rapidjson::Value& json_rendering_resource);
		dPtr<UniformBuffer> link();	

	private:
		std::string _name;
		std::vector<Uniform> _uniform_DA;
	};


	//-------------------------------------------------	
	//			ShaderComponentRenderingResource class
	//-------------------------------------------------
	class ShaderComponentRenderingResource : public RenderingResource
	{

		struct Attribute
		{
			Attribute(const std::string& stream_type, const std::string& attr_name)
			{
				_stream_type = stream_type;
				_attr_name = attr_name;
			}
			std::string _stream_type;
			std::string _attr_name;
		};
	public:
		ShaderComponentRenderingResource();
		~ShaderComponentRenderingResource();
		
		bool load(const rapidjson::Value& json_rendering_resource);

		dPtr<ShaderComponent> link(Assets<ShaderExtension>& shader_extension_DA,
			Assets<UniformBuffer>& uniform_buffer_DA);

	private:
		std::vector<std::string> _u_buffer_name_DA;
		std::vector<std::string> _extension_name_DA;
		std::vector<Attribute> _attribute_DA;
		std::vector<std::string> _shader_src;
		std::string  _name;
		UniformBufferRenderingResource _dynamic_u_buffer;
		std::string _shader_type;
	};

	//-------------------------------------------------	
	//			RenderTargetRenderingResource class
	//-------------------------------------------------
	class RenderTargetRenderingResource : public RenderingResource
	{
	public:
		RenderTargetRenderingResource();
		~RenderTargetRenderingResource();

		bool load(const rapidjson::Value& json_rendering_resource);

		dPtr<RenderTarget> link();
	private:
		Vec2f _size;		
		std::string _name;
		std::string _format;
	};
}