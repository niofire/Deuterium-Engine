#pragma once
#include "deuterium_markup_reader.h"
#include "deuterium_markup.h"
#include <fstream>
#include <string>
namespace deuterium
{

class DeuteriumMarkupLoader
{
public:
	DeuteriumMarkupLoader(void);
	~DeuteriumMarkupLoader(void);


	//Will throw error if file data integrity is broken
	void load_settings(const char* init_file);

private:

	void	load_node_data(MarkupNode* node);
	void	compile_and_link_node(MarkupNode* node);

};

}