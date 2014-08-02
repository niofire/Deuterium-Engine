// rapidjson/example/simpledom/simpledom.cpp`
#include "../Deuterium/3rdParty/rapidjson/writer.h"
#include "../Deuterium/3rdParty/rapidjson/stringbuffer.h"
#include "../Deuterium/3rdParty/rapidjson/document.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace rapidjson;
#define JSON_HAS_MEMBER(X,Y) if(!X.HasMember(Y)) { return false;} 
#define JSON_IS_STRING(X) if(!X.IsString()) { return false;} 
#define JSON_IS_ARRAY(X)  if(!X.IsArray()) { return false;} 


void remove_all_char(std::string& str, char c)
{
	for(int i = 0; i < str.size(); ++i)
	{
		if(str[i] == c)
		{
			str = str.substr(0,i) + str.substr(i + 1);
			i--;
		}
		
	}
}

bool is_json_array_member(const Value& json_parser,const char* member_name)
{
	if(!json_parser.HasMember(member_name))
	{
		return false;
	}
	if(!json_parser[member_name].IsArray())
	{
		return false;
	}
	return true;
}

bool load_data(const char* render_assets_package_name)
	{
		std::string json_string = "";
		std::ifstream file_in(render_assets_package_name);

		if(!file_in)
		{
			//file cannot open
			//LOAD ERROR
			return false;
		}

		while(!file_in.eof())
		{
			std::string line;
			std::getline(file_in,line);
			if(line.find("[[") != std::string::npos)
			{
				line.replace(line.find("[["),2,"\"");

				
			}
			if(line.find("]]") != std::string::npos)
			{
				
				line.replace(line.find("]]"),2,"\"");						
			}
			
			json_string += " " + line;
		}

	using namespace rapidjson;

	Document json_shader_data;
	remove_all_char(json_string,'\t');
	json_shader_data.Parse(json_string.c_str());
	
	std::string name;

	//catch any possible parse error
	if(json_shader_data.HasParseError())
	{
		ParseErrorCode c = json_shader_data.GetParseError();
		int s = json_shader_data.GetErrorOffset();
		std::string err_str = json_string.substr(s,40) + "...";
		return false;
	}

		if(!is_json_array_member(json_shader_data,"shader"))
		{
			return false;
		}

	const Value& shaders = json_shader_data["shader"];
	//cycle through all shader data
	for(int i = 0; i < shaders.Size(); ++i)
	{
		//---------------------------------------------
		//				Shader Name
		//---------------------------------------------
		JSON_HAS_MEMBER(shaders[i],"name")
		const Value& name_val = shaders[i]["name"];
		JSON_IS_STRING(name_val)
		std::string name = name_val.GetString();
		

		//---------------------------------------------
		//				Shader Includes
		//---------------------------------------------
		JSON_HAS_MEMBER(shaders[i],"include")
		const Value& include_array = shaders[i]["include"];
		JSON_IS_ARRAY(include_array)

		std::vector<std::string> include_DA;
		for(int j = 0; j < include_array.Size(); ++j)
		{
			JSON_IS_STRING(include_array[j])
			include_DA.push_back(include_array[j].GetString());
			include_DA[j].append(".shader_extension");
		}


		//---------------------------------------------
		//				Shader Type
		//---------------------------------------------


		//---------------------------------------------
		//				Shader Uniform Buffer
		//---------------------------------------------	
		JSON_HAS_MEMBER(shaders[i],"uniform_buffer")
		const Value& u_buffer_array = shaders[i]["uniform_buffer"];
		
		//go through all types
		struct UniformData
		{
			std::string name;
			std::string type;
		};


		//---------------------------------------------
		//				Shader Semantic
		//---------------------------------------------
		


		//---------------------------------------------
		//				Shader Source
		//---------------------------------------------
		JSON_HAS_MEMBER(shaders[i],"source");
		const Value& shader_source = shaders[i]["source"];
		JSON_IS_STRING(shader_source);
		std::string shader_source_str = shader_source.GetString();
	
		
	}

	bool t = json_shader_data["shader"].IsArray();
	const Value& a = json_shader_data["a"];
	//load in the name
	if(json_shader_data["shader"].IsObject())
	{

	}
	
	return true;
}
class foo
{
public:
	foo(){}
	~foo(){}

	void change_d(const int& a) {d = a; d++;}
	int d;
	
};

int main() {
	
	
	int q = 0;
	foo a; 
	a.change_d(q);
	int f =a.d;
    return 0;
}