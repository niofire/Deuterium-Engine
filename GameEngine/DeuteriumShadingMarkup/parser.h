#pragma once
#include "node.h"
#include <string>
#include "common.h"
namespace dsm
{
	class Parser
	{
	public:
		Parser(void);
		~Parser(void);

		Node::NodeType tag_type(std::string& content);

		std::vector<std::string> get_tag_content(U32 
	};
}
