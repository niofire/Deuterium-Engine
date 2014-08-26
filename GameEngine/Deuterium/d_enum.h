#pragma once
#include <string>
namespace deuterium
{
	class dEnum
	{
	public:

		dEnum(int enum_id, const std::string& enum_str)
		{
			_enum_id = enum_id;
			_enum_str = enum_str;
		}
		~dEnum();
		const int id() {return _enum_id;}
		const std::string& to_string() { return _enum_str;}
	private:
		int _enum_id;
		std::string _enum_str;
	};

}