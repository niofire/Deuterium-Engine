#pragma once
#include <string>
namespace deuterium
{
class ShaderExtension
{
public:
	ShaderExtension(void);
	~ShaderExtension(void);

	void set_extension(std::string source_str) { _extension = source_str;}
	
	const std::string& name() { return _name;}
	void set_name(const std::string& name) {_name = name;}
	const std::string& extension() {return _extension;}

	bool is_equal(ShaderExtension& ext);
private:
	std::string _name;
	std::string _extension;
};

}
