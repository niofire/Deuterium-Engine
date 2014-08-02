#pragma once
#include "global_data.h"
#include <vector>
#include <string>

namespace deuterium
{
class StringHelper
{
public:
	StringHelper() {}
	~StringHelper() {}

	static void trim(std::string& i_String);
	static void trim_front(std::string& i_String);
	static void trim_end(std::string& i_String);
	static bool	is_identical_string(std::string s1, std::string s2);
	static bool is_identical_string(const char* s1, const char* s2);
	static std::vector<std::string> split(char* string,char identifier);
	static void remove_all_char(std::string& str, char c);
};
}
