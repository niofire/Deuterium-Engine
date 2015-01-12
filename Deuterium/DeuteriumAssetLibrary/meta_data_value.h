#pragma once
#include <string>
#include <vector>
#include "3rdParty\rapidjson\stringbuffer.h"
#include "3rdParty\rapidjson\document.h"
#include "3rdParty\rapidjson\writer.h"
#include "3rdParty\rapidjson\error\en.h"
namespace deuterium
{
	
	class MetaDataValue
	{
		//------------------------------------------
		//			struct / enum Declaration
		//------------------------------------------
	public:
		enum ValueType 
		{
			INT,
			DOUBLE,
			STRING,
			BOOL,
			ARRAY,
		};


	public:
		MetaDataValue();
		~MetaDataValue(); 

		//------------------------------------------
		//			Mutators / Accessors
		//------------------------------------------
		
		//Name of the data value, array elements will share the same name
		const		std::string& name() { return _name;}
		void		set_name(const std::string& name) { _name = name;}

		int			size();
		void*		value();


		//------------------------------------------
		//			Meta Value Core Functions
		//------------------------------------------
		void		clear();
		bool		set_value(const rapidjson::Value& v);
		bool		is_null() const { return *this == MetaDataValue::null_value;}
		//------------------------------------------
		//			Operator Overload
		//------------------------------------------
		inline bool operator==(const MetaDataValue& rhs) const {return _name.compare(rhs._name) == 0 && _vPtr == rhs._vPtr;}
		inline bool operator!=(const MetaDataValue& rhs) const { return !(*this == rhs);}
		//------------------------------------------
		//			Member variables
		//------------------------------------------
	public:
		static const MetaDataValue null_value;
	private:
		std::string _name;
		void* _vPtr;



	};
}
