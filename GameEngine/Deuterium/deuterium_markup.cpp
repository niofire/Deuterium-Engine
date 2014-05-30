#include "deuterium_markup.h"

namespace deuterium
{
	const char* MarkupNode::to_string(MarkupNodeType type)
	{
		switch(type)
		{
		case MARKUP_PASS:
			return "pass";
		case MARKUP_SHADER:
			return "shader";
		case MARKUP_TECHNIQUE:
			return "technique";
		case MARKUP_UNIFORM_BUFFER:
			return "uniform_buffer";
		case MARKUP_SHADER_SEMANTIC:
			return "sampler";
		case MARKUP_SHADER_SAMPLER:
			return "sampler";
		case MARKUP_SHADER_SOURCE:
			return "source";
		}
	}

	MarkupNode::MarkupNodeType MarkupNode::to_enum(std::string type_str)
	{
		for(int i = 0; i < NUMBER_OF_MARKUP_NODE_TYPES; ++i)
		{
			if(StringHelper::is_identical_string(to_string((MarkupNodeType)i),type_str))
				return (MarkupNodeType)i;
		}
		return NUMBER_OF_MARKUP_NODE_TYPES;
		

	}

	MarkupNode* MarkupNode::create_new_node(std::string tag)
	{
		switch(to_enum(tag))
		{
		case MARKUP_PASS:
			return new Markup_Pass;
		case MARKUP_SHADER:
			return new Markup_Shader;
		case MARKUP_TECHNIQUE:
			return new Markup_Technique;
		case MARKUP_UNIFORM_BUFFER:
			return new Markup_UniformBuffer;
		case MARKUP_SHADER_SEMANTIC:
			return new Markup_ShaderSemantic;
		case MARKUP_SHADER_SAMPLER:
			return new Markup_ShaderSampler;
		case MARKUP_SHADER_SOURCE:
			return new Markup_ShaderSource;
		case NUMBER_OF_MARKUP_NODE_TYPES:
			return NULL;
		default:
			return NULL;
		}
	}


}