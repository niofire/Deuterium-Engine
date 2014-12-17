#include "renderer_settings.h"
#include <string>
namespace deuterium
{

RendererSettings::RendererSettings(void)
{
}


RendererSettings::~RendererSettings(void)
{
}

void RendererSettings::load_shaders(const char* settings_file)
{
	std::ifstream settings_fstream(settings_file);

	//check if file opened correctly
	if(!settings_fstream)
	{
		//file did not open..
		return;
	}

	while(!settings_fstream.eof())
	{
		std::string str;
		std::getline(settings_fstream,str);

		//check for shader_source tag
		if(str.find("<") != std::string::npos)
		{

		}

	}

	

}

}