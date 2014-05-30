#pragma once
#include <vector>
#include <fstream>
namespace deuterium
{
class RendererSettings
{
public:
	RendererSettings(void);
	~RendererSettings(void);
	
	void	load_shaders(const char* settings_file);
};

}