#include "meta_data_value.h"
#include "void_d_ptr.h"
namespace deuterium
{

	MetaDataValue::MetaDataValue(void)
	{
		_name = "";
		_vPtr = NULL;
	}


	MetaDataValue::~MetaDataValue(void)
	{
	}

	//clear value
	void MetaDataValue::clear()
	{
		if(_vPtr)
		{
			delete _vPtr;
			_vPtr = NULL;
		}
	}

	bool MetaDataValue::set_value(const rapidjson::Value& v)
	{
		if( v.IsDouble())
		{
			_vPtr = new double(v.GetDouble());
		}
		else if(v.IsBool())
		{
			_vPtr = new bool(v.GetBool());
		}
		else if(v.IsInt())
		{
			_vPtr = new int(v.GetInt());
		}
		else if(v.IsString())
		{
			_vPtr = new std::string(v.GetString());
		}
		else
			return false;
		return true;

	}


}