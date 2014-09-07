#include "renderer.h"
#include "resource_loader.h"
namespace deuterium
{
void Renderer::init(int width, int height)
{
	//Create the gl_context and sets the default back_buffer settings
	init_gl_context(width,height);

	glViewport(0,0,width,height);
	resize_window(width,height);

	this->_debug_camera.set_name("MainCamera");
	/*
	if(!this->load_render_pipe())
	{
		while(!dErrorStack::get_instance().empty())
		{
			std::cout << dErrorStack::get_instance().pop() << std::endl;
		}
	}
	
	//Compile all render pipe assets
	this->_render_pipe.compile_render_pipe();
	*/
}

bool Renderer::load_render_pipe()
{
	//Fetch render_settings file
	std::ifstream file_in(s_render_settings_config_filepath);

	if(!file_in)
	{
		dErrorStack::get_instance().push(std::string("Could not open render_settings.config file located at path:" + std::string(s_render_settings_config_filepath)));
		return false;
	}

	std::vector<std::string> file_content;
	while(!file_in.eof())
	{
		std::string line;

		std::getline(file_in,line);
		file_content.push_back(line);
	}

	std::string render_pipe_macro = "#RENDER_PIPE";
	std::string render_pipe_filepath = "";
	ResourceLoader loader;
	for(int i = 0; i < file_content.size(); ++i)
	{
		if(file_content[i].find(render_pipe_macro) != std::string::npos)
		{

			//---------------------------------------
			//			Load Render Pipe Resources
			//---------------------------------------

			//Get Render pipe filepath
			std::string render_pipe_filepath = file_content[i];
			render_pipe_filepath = render_pipe_filepath.substr( render_pipe_filepath.find(render_pipe_macro) + render_pipe_macro.size());
			StringHelper::trim(render_pipe_filepath);

			/*if(!_render_pipe.load_render_pipe(render_pipe_filepath.c_str()))
			{
				D_ERROR("The .render_pipe file did not load correctly!");
				return false;
			}*/
		}
	}

	return true;
}


void Renderer::init_gl_context(int width, int height)
{
		
#ifdef EMSCRIPTEN
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_init Error:" << SDL_GetError() << std::endl;
	}
#else
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_init Error:" << SDL_GetError() << std::endl;
	}
#endif
	//open_gl settings, usually default, just for template
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,        8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,      8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,       8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,      8);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,      16);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,        32);

	SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,    8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,    8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,    8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,    8);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);

#ifdef EMSCRIPTEN
	l_DisplayScreen = SDL_SetVideoMode(
		width, height, 32,
		  SDL_ANYFORMAT | SDL_OPENGL);
#else
	_sdl_display_window = SDL_CreateWindow("SDL2 OpenglExample", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, 1,1,
		SDL_WINDOW_OPENGL);

	if(_sdl_display_window == nullptr)
	{
		std::cout << "SDL_CreateWindow Error:" << SDL_GetError() << std::endl;
	}
	_sdl_opengl_context = SDL_GL_CreateContext(_sdl_display_window);
	


	GLenum err = glewInit();
#endif
}
}