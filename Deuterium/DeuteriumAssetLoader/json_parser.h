#pragma once
#include <string>
#include <fstream>

#include "string_helper.h"
#include "d_error_stack.h"
#include "3rdParty\rapidjson\stringbuffer.h"
#include "3rdParty\rapidjson\document.h"
#include "3rdParty\rapidjson\writer.h"
#include "3rdParty\rapidjson\error\en.h"



namespace deuterium
{
	
class JsonParser
{
public:
	JsonParser(void);
	~JsonParser(void);

	static std::string get_json_from_file(const char* filename);
	static bool load_json_document(rapidjson::Document& d, std::string& str);
	static bool has_member(const rapidjson::Value& value, const char* member, const char* filename);
	static bool is_string(const rapidjson::Value& value, const char* member, const char* filename);
	static bool is_array(const rapidjson::Value& value, const char* member, const char* filename);

	static bool fetch_string(const rapidjson::Value& json_parser, std::string& str,const char* member_name, const char* filename);
	static bool fetch_string_DA(const rapidjson::Value& json_parser, std::vector<std::string>& str_DA, const char* member_name, const char* filename);


private:

};
}
