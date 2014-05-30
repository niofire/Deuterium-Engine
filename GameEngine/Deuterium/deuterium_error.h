#pragma once
namespace deuterium
{

class DeuteriumError
{

public:
	DeuteriumError(void);
	DeuteriumError(const char* msg) { _message = msg;}
	~DeuteriumError(void);

	virtual const char* message()	{return _message;}
private:
	const char* _message;
};

}