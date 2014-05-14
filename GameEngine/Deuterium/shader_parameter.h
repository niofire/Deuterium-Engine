#include <string>
#include "global_data.h"

namespace deuterium
{
class ShaderParameter
{
public:

	//----------------------------------------------------
	//				struct/enum
	//----------------------------------------------------
	enum SemanticId
	{
		WORLDVIEW = 0,
		WORLDVIEWPROJ,
		TEXTURESAMPLER,
		NORMALSAMPLER,
		TIME,
		UNKNOWN,
	};

	
	struct ParameterData
	{
		std::string				_name;
		SemanticId				_id;
		DeuteriumPrimitiveType	_type;
		void*					_value;
		U32						_uniform_location;
	};


	//----------------------------------------------------
	//				Constructor / destructor
	//----------------------------------------------------
	ShaderParameter(std::string i_ParameterType, std::string i_ParameterName,GLint i_UniformLocation);
	ShaderParameter();
	~ShaderParameter();

	void						UpdateParameter(void* i_Value);
	void						UpdateProgramParameter();
	//----------------------------------------------------
	//				Accessors
	//----------------------------------------------------
	const char*					GetParameterName() {return _parameter_data._name.c_str();}
	SemanticId					GetShaderParameterId() {return _parameter_data._id;}
	DeuteriumPrimitiveType					GetParameterType()	{return _parameter_data._type;}
	void*						GetParameterValue()	{return	_parameter_data._value;}
	bool						IsParameterInitialized()	{return _is_initialized;}

private:
	bool				_is_initialized;
	ParameterData		_parameter_data;
};
}