#include "uniform_type.h"


namespace dsm
{
	UniformType::UniformType()
	{

	}

	UniformType::~UniformType()
	{

	}

	std::vector<UniformType::UType> UniformType::string_to_type(std::string str)
	{
		std::vector<UType> type_vec;
		for(int i = 0; i < UNKOWN_TYPE; ++i)
		{
			std::string type_str = UniformType::type_to_string((UType)i);
			int type_pos = str.find(type_str);
			if(type_pos != std::string::npos)
			{
				while(type_pos != std::string::npos)
				{
					type_vec.push_back((UType)i);
					str = str.substr(0,type_pos) + str.substr(type_pos + type_str.size());
					type_pos = str.find(type_str);
				}
			}
		}
		return type_vec;
	}

	std::vector<UniformType::USemantic> UniformType::string_to_semantic(std::string str)
	{
		std::vector<USemantic> type_vec;
		for(int i = 0; i < UNKNOWN_SEMANTIC; ++i)
		{
			std::string type_str = UniformType::semantic_to_string((USemantic)i);
			int type_pos = str.find(type_str);
			if(type_pos != std::string::npos)
			{
				while(type_pos != std::string::npos)
				{
					type_vec.push_back((USemantic)i);
					str = str.substr(0,type_pos) + str.substr(type_pos + type_str.size());
					type_pos = str.find(type_str);
				}
			}
		}
		return type_vec;
	}


	std::string UniformType::type_to_string(UniformType::UType type)
	{
		switch(type)
		{
		case FLOAT:
			return "float";
		case FLOAT2:
			return "float2";
		case FLOAT3:
			return "float3";
		case FLOAT4:
			return "float4";
		case MAT3:
			return "mat3";
		case MAT4:
			return "mat4";
		case INT:
			return "int";
		case SAMPLER2D:
			return "sampler2d";
		default:
			return "Unknown";

		}
	}


	std::string UniformType::semantic_to_string(UniformType::USemantic semantic)
	{
		switch(semantic)
		{
		case POSITION0:
			return "POSITION0";
		case POSITION1:
			return "POSITION1";
		case NORMAL0:
			return "NORMAL0";
		case NORMAL1:
			return "NORMAL1";
		case BINORMAL0:
			return "BINORMAL0";
		case TEXCOORD0:
			return "TEXCOORD0";
		case TEXCOORD1:
			return "TEXCOORD1";
		case TEXCOORD2:
			return "TEXCOORD2";
		case TEXCOORD3:
			return "TEXCOORD3";
		case TEXCOORD4:
			return "TEXCOORD4";
		case TEXCOORD5:
			return "TEXCOORD5";
		case TEXCOORD6:
			return "TEXCOORD6";
		case TEXCOORD7:
			return "TEXCOORD7";
		default:
			return "UNKNOWN";
		}

	}
}