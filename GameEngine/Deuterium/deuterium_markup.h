#pragma once
#include <vector>
#include <string>
#include "string_helper.h"

namespace deuterium
{

	class MarkupNode
	{


	public:
				enum MarkupNodeType
		{
			MARKUP_SHADER,
			MARKUP_PASS,
			MARKUP_TECHNIQUE,
			MARKUP_SHADER_SOURCE,
			MARKUP_SHADER_SEMANTIC,
			MARKUP_UNIFORM_BUFFER,
			MARKUP_SHADER_SAMPLER,
			NUMBER_OF_MARKUP_NODE_TYPES,
		};

		MarkupNode(MarkupNodeType type) { _type = type;}
		~MarkupNode();
		

		std::vector<MarkupNode*> _node_pointer_list;
		static MarkupNode* create_new_node(std::string tag);
		std::vector<std::string> _node_content;
		virtual void load_data_from_content()	=	0;

		const MarkupNodeType type() const	{return _type;}
	private:
		MarkupNodeType _type;
		static const char* to_string(MarkupNodeType type);
		static MarkupNodeType	to_enum(std::string type_str);



		


	};

	//Abstract class of the markup node
	//which is used to define specific rendering
	//component data
	class Markup_Shader : public MarkupNode
	{
	public:
		Markup_Shader() : MarkupNode(MARKUP_SHADER) {};
		~Markup_Shader();
		void load_data_from_content();
	private:

	};

	//stores shader as well as render states information for the pass
	class Markup_Pass : public MarkupNode
	{
	public:
		Markup_Pass() : MarkupNode(MARKUP_PASS) {};
		~Markup_Pass();
		void load_data_from_content();
	private:

	};

	//contains a set of passes
	class Markup_Technique : public MarkupNode
	{
	public:
		Markup_Technique() :  MarkupNode(MARKUP_TECHNIQUE) {};
		~Markup_Technique();
		void load_data_from_content();
	private:

	};

	//contains sampler and sampler state specification
	class Markup_ShaderSampler : public MarkupNode
	{
	public:
		Markup_ShaderSampler() :  MarkupNode(MARKUP_SHADER_SAMPLER) {};
		~Markup_ShaderSampler();
		void load_data_from_content();
	private:

	};
	
	//Contains the shader source code
	class Markup_ShaderSource : public MarkupNode
	{
	public:
		Markup_ShaderSource() :  MarkupNode(MARKUP_SHADER_SOURCE) {};
		~Markup_ShaderSource();
		void load_data_from_content();
	private:
	};

	//Stores shader semantic information
	class Markup_ShaderSemantic : public MarkupNode
	{
	public:
		Markup_ShaderSemantic() :  MarkupNode(MARKUP_SHADER_SEMANTIC) {};
		~Markup_ShaderSemantic();
		void load_data_from_content();
	private:
	};
	
	//Contains uniform buffer information
	class Markup_UniformBuffer : public MarkupNode
	{
	public:
		Markup_UniformBuffer() :  MarkupNode(MARKUP_UNIFORM_BUFFER) {};
		~Markup_UniformBuffer();
		void load_data_from_content();
	private:
	};
	
	
	



}