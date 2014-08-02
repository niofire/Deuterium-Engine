#pragma once
#include "../Deuterium/d_ptr.h"
#include "render_pipe.h"
#include "dsm_error_stack.h"
#include <string>
#include <vector>
#include <fstream>
#include "parser.h"
namespace dsm
{
	class Loader
	{
	public:
		Loader(void);
		~Loader(void);

		d_ptr<RenderPipe> load_rendering_pipeline(std::string render_pipe_filename, std::string render_assets_package_filename);
	
	private:

		d_ptr<Node> load_render_pipe(std::string filename);

		//returns a list of shader, technique and pass nodes
		std::vector< d_ptr<Node> > load_assets_package(std::string filename);

		std::vector<d_ptr<Node>> load_shader_data(std::string filename);
		d_ptr<Node> load_shader_extension(std::string filename);
	
	};


}
