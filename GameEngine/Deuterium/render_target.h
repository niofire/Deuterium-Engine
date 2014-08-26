#pragma once
#include "global_data.h"
#include "deuterium_math.h"
#include <string>
namespace deuterium
{
class RenderTarget
{
public:
	RenderTarget();
	RenderTarget(bool is_back_buffer);
	RenderTarget(U32 width, U32 height);
	RenderTarget(const char* name);
	RenderTarget(const char* name, U32 width, U32 height);
	~RenderTarget(void);


	const Vec2f& size() { return _size;}
	const std::string& name() {return _name;}
	void initialize();
	void bind();
	bool is_back_buffer() { return _is_backbuffer;}
private:
	bool _is_backbuffer;
	Vec2f _size;
	std::string _name;
	U32 _rt_handle;
};

}