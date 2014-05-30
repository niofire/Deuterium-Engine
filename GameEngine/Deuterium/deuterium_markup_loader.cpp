#include "deuterium_markup_loader.h"


namespace deuterium
{
DeuteriumMarkupLoader::DeuteriumMarkupLoader(void)
{
}


DeuteriumMarkupLoader::~DeuteriumMarkupLoader(void)
{
}

void DeuteriumMarkupLoader::load_node_data(MarkupNode* markup_node)
{
	//load every child node..
	for(int i = 0 ; i < markup_node->_node_pointer_list.size(); ++i)
	{
		this->load_node_data(markup_node->_node_pointer_list[i]);
	}

	switch(markup_node->type())
	{
	case MarkupNode::MarkupNodeType::MARKUP_SHADER:
		Markup_Shader* node = (Markup_Shader*)markup_node;
		
		break;
	case MarkupNode::MarkupNodeType::MARKUP_PASS:
		Markup_Pass* node = (Markup_Pass*)markup_node;
		break;
	case MarkupNode::MarkupNodeType::MARKUP_SHADER_SAMPLER:
		Markup_ShaderSampler* node = (Markup_ShaderSampler*)markup_node;
		break;
	case MarkupNode::MarkupNodeType::MARKUP_SHADER_SEMANTIC:
		Markup_ShaderSemantic* node = (Markup_ShaderSemantic*)markup_node;
		break;
	case MarkupNode::MarkupNodeType::MARKUP_SHADER_SOURCE:
		Markup_ShaderSource* node = (Markup_ShaderSource*)markup_node;
		break;
	case MarkupNode::MarkupNodeType::MARKUP_TECHNIQUE:
		Markup_Technique* node = (Markup_Technique*)markup_node;
		break;
	case MarkupNode::MarkupNodeType::MARKUP_UNIFORM_BUFFER:
		Markup_UniformBuffer* node = (Markup_UniformBuffer*)markup_node;
		break;


	}


	//
	for(int i = 0; i < node_list.size(); ++i)
	{
		switch(node_list[i]->type())
		{
		case MarkupNode::MARKUP_SHADER:
			Markup_Shader* node = (Markup_Shader*)node_list[i];

			break;
		case MarkupNode::MARKUP_SHADER_SAMPLER:
			Markup_ShaderSampler* node = (Markup_ShaderSampler*)node_list[i];
			
			break;
		case MarkupNode::MARKUP_SHADER_SEMANTIC:
			Markup_ShaderSemantic* node = (Markup_ShaderSemantic*)node_list[i];
			
			break;
		case MarkupNode::MARKUP_SHADER_SOURCE:
			Markup_ShaderSource* node = (Markup_ShaderSource*)node_list[i];
			break;
		case MarkupNode::MARKUP_TECHNIQUE:
			Markup_Technique* node = (Markup_Technique*)node_list[i];
			break;
		case MarkupNode::MARKUP_UNIFORM_BUFFER:
			Markup_UniformBuffer* node = (Markup_UniformBuffer*)node_list[i];
			break;
		case MarkupNode::MARKUP_PASS:
			Markup_Pass* node = (Markup_Pass*)node_list[i];
			break;
		default:
			break;

		}
	}
}

void DeuteriumMarkupLoader::load_settings(const char* init_filename)
{
	//get the render_data files from the init file
	
	std::ifstream file_in(init_filename);
	if(!file_in)
		return;

	DeuteriumMarkupReader::is_opening_tag("render_settings");
	DeuteriumMarkupReader reader;

	bool is_comment = false;
	while(!file_in.eof())
	{
		std::string line;
		std::getline(file_in,line);

		#pragma region comment checking
		if(line.find("*/") != std::string::npos)
		{
			is_comment = false;
			line = line.substr(line.find("*/") + 2);
		}
		
		if(line.find("//") != std::string::npos || is_comment)
			continue;
		if(line.find("/*") != std::string::npos)
		{
			is_comment = false;
			continue;
		}
		#pragma endregion




	}
	
	std::vector<MarkupNode*> node_list = reader.process_markup_file(settings_filename);

	for(int i = 0; i < node_list.size(); ++i)
	{
		this->load_node(node_list[i],NULL);
	}

	for(int i = 0; i < node_list.size(); ++i)
	{
		this->compile_and_link_node(node_list[i]);
	}


}
}