#pragma once
#include <string>
#include <vector>
namespace dsm
{
class UniformType
{
public:

	enum UType
	{
		FLOAT,
		FLOAT2,
		FLOAT3,
		FLOAT4,
		MAT3,
		MAT4,
		INT,
		SAMPLER2D,
		UNKOWN_TYPE,
	};

	enum USemantic
	{
		POSITION0,
		POSITION1,
		NORMAL0,
		NORMAL1,
		BINORMAL0,
		TEXCOORD0,
		TEXCOORD1,
		TEXCOORD2,
		TEXCOORD3,
		TEXCOORD4,
		TEXCOORD5,
		TEXCOORD6,
		TEXCOORD7,
		UNKNOWN_SEMANTIC,
	};

		struct Uniform
	{
		UniformType::UType _type;
		std::string _uniform_name;
	};
		struct UniformSemantic
		{
			Uniform _uniform;
			std::string _semantic_name;
		};
	UniformType(void);
	~UniformType(void);

	static std::vector<UType> string_to_type(std::string str);
	static std::string type_to_string(UType type);

	static std::vector<USemantic> string_to_semantic(std::string str);
	static std::string semantic_to_string(USemantic type);

	
private:


};

}