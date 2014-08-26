#include "json_parser.h"

namespace deuterium
{
	JsonParser::JsonParser(void)
	{

	}


	JsonParser::~JsonParser(void)
	{
		
	}

	bool JsonParser::load_json_document(rapidjson::Document &d, std::string& str)
	{
		using namespace rapidjson;
	
		d.Parse(str.c_str());
	
		std::string name;

		//catch any possible parse error
		if(d.HasParseError())
		{
			
			ParseErrorCode err_code = d.GetParseError();
			std::string err_str =  GetParseError_En(err_code);
			int err_offset = d.GetErrorOffset();
			err_str =  err_str + "Error located at: " + str.substr(err_offset,20);
			DeuteriumErrorStack::get_instance().push(DeuteriumError(std::string("Json Parsing error" + err_str).c_str()));
			return false;
		}
		return true;
	}


	std::string JsonParser::get_json_from_file(const char* filename)
	{
		std::string json_string = "";
		std::ifstream file_in(filename);
		
		if(!file_in)
		{
			//file cannot open
			
			return "";
		}
		//parser through file
		bool is_multiline_complete = true;
		while(!file_in.eof())
		{
			std::string line;
			std::getline(file_in,line);
			if(line.find("[[") != std::string::npos)
			{
				line.replace(line.find("[["),2,"\"");
				is_multiline_complete = false;
				
			}
			if(line.find("]]") != std::string::npos)
			{
				line.replace(line.find("]]"),2,"\"");	
				is_multiline_complete = true;
			}
			
			json_string += " " + line;
		}
		if(!is_multiline_complete)
		{
			std::string err_str("Missing \"]]\" in " + std::string(filename));
			D_ERROR(err_str.c_str());
			return "";
		}

		StringHelper::remove_all_char(json_string,'\t');
		
		return json_string;
	}

	bool JsonParser::has_member(const rapidjson::Value& value, const char* member, const char* filename)
	{
		if(!value.HasMember(member))
		{
			std::string str = "The file " + std::string(filename) + " with member " + std::string(member) + ": Member not found.";
			DeuteriumErrorStack::get_instance().push(DeuteriumError(str));
			return false;
		}
		return true;
	}

	bool JsonParser::is_string(const rapidjson::Value& value, const char* member, const char* filename)
	{
		if(!value.IsString())
		{
			DeuteriumErrorStack::get_instance().push(DeuteriumError(std::string("The file " + std::string(filename) + " with member " + member + ": Member is not a string.")));
			return false;
		}
		return true;
	}

	bool JsonParser::is_array(const rapidjson::Value& value, const char* member, const char* filename)
	{
		if(!value.IsArray())
		{
			DeuteriumErrorStack::get_instance().push(DeuteriumError(std::string("The file " + std::string(filename) + " with member " + member + ": Member is not an array.")));
			return false;
		}
		return true;
	}

}