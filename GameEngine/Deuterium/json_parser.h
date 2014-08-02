#pragma once
#include <string>
#include <fstream>
#include "string_helper.h"
#include "3rdParty\rapidjson\stringbuffer.h"
#include "3rdParty\rapidjson\document.h"
#include "3rdParty\rapidjson\writer.h"
#include "3rdParty\rapidjson\error\en.h"
#define JSON_HAS_MEMBER_ERROR(member_name,filename) "The file " + std::string(filename) + "is missing the following member: " + std::string(member_name)
#define JSON_HAS_MEMBER(value,member,filename) if(!value.HasMember(member)) {D_ERROR(JSON_HAS_MEMBER_ERROR(member,filename)) return false;} 

#define JSON_IS_STRING_ERROR(member_name,filename) "The file " + std::string(filename) + " with member " + std::string(member_name) + ": Member is not a string."
#define JSON_IS_STRING(value,member,filename) if(!value.IsString()) {D_ERROR(JSON_IS_STRING_ERROR(member,filename)) return false;} 

#define JSON_IS_ARRAY_ERROR(member_name,filename) "The file " + std::string(filename) + " with member " + std::string(member_name) + ": Member is not an array."
#define JSON_IS_ARRAY(value,member,filename)  if(!value.IsArray()) { D_ERROR(JSON_IS_ARRAY_ERROR(member,filename)) return false;} 


namespace deuterium
{
	
class JsonParser
{
public:
	JsonParser(void);
	~JsonParser(void);

	static std::string get_json_from_file(const char* filename);
	static bool load_json_document(rapidjson::Document& d, std::string& str);
	

private:

};
}
