#pragma once
#include "node.h"
#include <string>
#include "dsm_error_stack.h"
#include "common.h"
namespace dsm
{
	struct DsmTag
	{
		Node::NodeType _type;
		U32 _opening_tag_index;
		U32 _closing_tag_index;
		std::vector<DsmTag> _inner_tags;
	};

	class Parser
	{
	public:
		Parser(void);
		Parser(std::vector<std::string>& content, std::string filename) { _content = content; _filename = filename;}
		~Parser(void);

		void set_content(std::vector<std::string>& content, std::string filename) { _content = content; _filename = filename;}

		static Node::NodeType tag_type(std::string& content);
		static std::string node_to_string(Node::NodeType type);
		std::vector<DsmTag> get_tag_tree();
		S32 get_next_opening_tag_index(U32 index);
		S32 get_next_closing_tag_index(U32 index);

		bool is_opening_tag(std::string&);
		bool is_closing_tag(std::string&);
		std::vector<std::string> extract_content(U32 opening_tag_index);

		void remove_tag(std::string&, Node::NodeType);


	private:
		std::string _filename;
		std::vector<std::string> _content;

	};
}
