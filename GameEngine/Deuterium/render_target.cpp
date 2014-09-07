#include "render_target.h"
#include "renderer.h"
namespace deuterium
{

RenderTarget::RenderTarget(void)
{
	this->_rt_handle = 0;
	this->_name ="";
	this->_size = g_data._renderer_ptr->window_size();
	_is_backbuffer = false;
}

RenderTarget::RenderTarget(bool is_backbuffer)
{
	this->_rt_handle = 0;
	
	this->_size = g_data._renderer_ptr->window_size();

	_is_backbuffer = is_backbuffer;
	if(is_backbuffer)
		this->_name ="back_buffer";
	else
		this->_name = "";
}


RenderTarget::RenderTarget(U32 width, U32 height)
{
	this->_rt_handle = 0;
	this->_name ="";
	this->_size = Vec2f(width,height);
	_is_backbuffer = false;
}

RenderTarget::RenderTarget(const char* name)
{
	this->_rt_handle = 0;
	this->_name = name;
	this->_size = g_data._renderer_ptr->window_size();
	_is_backbuffer = false;
}


RenderTarget::RenderTarget(const char* name, U32 width, U32 height)
{
	this->_rt_handle = 0;
	this->_name = name;
	this->_size = Vec2f(width,height);
	_is_backbuffer = false;
}



RenderTarget::~RenderTarget(void)
{
}

void RenderTarget::initialize()
{

}

void RenderTarget::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER,_rt_handle);
}

void RenderTarget::set_format(const std::string& format)
{

}
}