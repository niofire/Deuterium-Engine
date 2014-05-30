#pragma once
#include "deuterium_markup.h"
#include <vector>
#include <string>
#include <fstream>
#include "global_data.h"
#include <stack>
namespace deuterium

{
	
class DeuteriumMarkupReader
{
public:
	DeuteriumMarkupReader(void);
	~DeuteriumMarkupReader(void);


	//parses the passe file for all of the rendering markup it contains
	//and return a vector containing each of the head markup nodes
	std::vector<MarkupNode*> process_markup_file( const char* markup_filename);
	
	//returns whether the passed string is an opening tag, < tag >
	static bool is_opening_tag(std::string );

	//returns whether the passed string is a closing tag, </tag>
	static bool is_closing_tag(std::string str);

private:


	//remove brackets out of the tag string
	std::string clean_up_tag(std::string);

	
	//create and returns a node tree of all the nodes contained within the current tag
	MarkupNode* fetch_node_tree(std::vector<std::string>& str_vec, U32& opening_tag_index);


	std::stack< std::vector< std::string> > _markup_node_hierarchy_stack;


	
};

}