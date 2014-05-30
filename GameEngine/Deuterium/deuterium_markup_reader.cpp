#include "deuterium_markup_reader.h"


namespace deuterium
{
DeuteriumMarkupReader::DeuteriumMarkupReader(void)
{
}


DeuteriumMarkupReader::~DeuteriumMarkupReader(void)
{
}

bool DeuteriumMarkupReader::is_opening_tag(std::string str )
{
	std::string line(str);
	
	if(line.find("<") != std::string::npos 
		&& line.find(">") != std::string::npos 
		&& line.find("/") == std::string::npos)
		return true;
	return false;

}

bool DeuteriumMarkupReader::is_closing_tag(std::string str)
{
		std::string line(str);
	
	if(line.find("</") != std::string::npos 
		&& line.find(">") != std::string::npos)
		return true;
	return false;
}

MarkupNode* DeuteriumMarkupReader::fetch_node_tree(std::vector<std::string>& str_vec, U32& index)
{
	
	//Create markup node corresponding to the tag
	MarkupNode* node = MarkupNode::create_new_node( clean_up_tag( str_vec[ index ]) );	

	index++;
	while(!is_closing_tag(str_vec[index]))
	{
		
		if(is_opening_tag(str_vec[index]))
		{
			//new node is created here	
			node->_node_pointer_list.push_back(fetch_node_tree(str_vec,index));
			continue;
		}

		node->_node_content.push_back(str_vec[index]);
		index++;
	}
	index++;

	//parse the gathered content of the node and fill in the 
	node->load_data_from_content();
	return node;
}

std::string	DeuteriumMarkupReader::clean_up_tag(std::string tag)
{
	U32 start = 0,finish = 0;
	
	start = tag.find("</") != std::string::npos ? tag.find("</") : tag.find("<");
	finish = tag.find(">");

	if(start != std::string::npos && finish != std::string::npos)
	{
		tag = tag.substr(start,finish-start);
	}

	StringHelper::trim(tag);

	return tag;
}

std::vector<MarkupNode*> DeuteriumMarkupReader::process_markup_file(const char* markup_filename)
{
	std::vector<MarkupNode*> node_vec;
	
	//open filestream
	std::ifstream file_in(markup_filename);

	//check if file opened properly
	if(file_in)
	{
		//file did not open
		//TODO error handling
		return node_vec;
	}
	

	std::vector<std::string> file_content;
	while(!file_in.eof())
	{	
		std::string str;
		std::getline(file_in,str);
		file_content.push_back(str);
	}

	//Load in all markup node trees
	for(U32 i = 0 ; i < file_content.size(); ++i)
	{
		if(is_opening_tag(file_content[i].c_str()))
		{
			node_vec.push_back(fetch_node_tree(file_content,i));
		}
	}

	return node_vec;
	
	}
}