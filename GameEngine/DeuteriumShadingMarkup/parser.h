#pragma once
#include "node.h"
#include <string>
#include "dsm_error_stack.h"
#include "common.h"
#include "../Deuterium/string_helper.h"
#include "uniform_type.h"
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


		std::vector<DsmTag> get_tag_tree();

		S32 get_next_opening_tag_index(U32 index);
		S32 get_next_closing_tag_index(U32 index);

		static bool is_opening_tag(std::string&);
		static bool is_closing_tag(std::string&);
		static bool is_tag_type(std::string& content,Node::NodeType type);
		static void trim_end(std::string&);
		static void trim_front(std::string&);
		static void trim(std::string&);
		static std::vector<UniformType::UType> get_uniform_type(std::string& str);
		static Node::NodeType tag_type(std::string& str);
		static std::string node_to_string(Node::NodeType type);
		static std::vector<U32> find_substr_indexes(std::string ori_str, const char* substr);
		static std::vector<std::string> get_tags_from_string(std::string& str);

		std::vector< Node::NodeData > extract_content(Node::NodeType node_type);

		void remove_tag(std::string&, Node::NodeType);
		bool has_tag_integrity();
	private:
		
		std::string _filename;
		std::vector<std::string> _content;

	};
}
