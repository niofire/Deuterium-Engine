#pragma once
#include "d_typedef.h"
#include "global_data.h"
#include "3rdParty\SDL2\include\SDL.h"
class RenderContext
{
private:
	struct FrameBufferSettings
	{
		U8 numberOfBuffers;
		U8 red;
		U8 green;
		U8 blue;
		U8 alpha;
		U8 depth;
		U8 stencil;
	};
public:
	RenderContext(void);
	~RenderContext(void);


	//------------------------------------------------
	//			Render Context Parameters
	//------------------------------------------------
	void set_frame_buffer_size(U8 r, U8 g, U8 b, U8 a);
	void set_depth_buffer_size(U8 d, U8 s);
	void set_num_buffers(U8 num);
	void set_default_settings();

	//Create a rendering context with the current settings.
	//If a context already exists, it will be replaced by a new one.
	//Pass in null for browser
	void create_context(SDL_Window* window);

	void destroy_context();

	void setup_context();
private:
	void init_SDL();
	void bind_context_attributes();



private:
	FrameBufferSettings _settings;
	
#ifdef DEUTERIUM_PC
	SDL_GLContext _context; 
#endif
};

