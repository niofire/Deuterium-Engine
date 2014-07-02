#include "loader.h"
#define COULD_NOT_OPEN_MSG(X) "Could not open file " + X + "."

namespace dsm 
{
Loader::Loader(void)
{
}


Loader::~Loader(void)
{
}


const char* Loader::get_error()
{
	if(_error_stack.empty())
		return "";
	else
		return _error_stack.pop();

}

d_ptr<RenderPipe> Loader::load_rendering_pipeline(std::string render_pipe_filename, std::string render_assets_package_filename)
{
	d_ptr<RenderPipe> render_pipe(new RenderPipe());

	std::vector<d_ptr<Node> > ra_package_node;
	ra_package_node = load_assets_package(render_assets_package_filename);

	
}
d_ptr<Node> load_render_pipe(std::string filename) 
{

}

std::vector< d_ptr<Node> > Loader::load_assets_package(std::string filename)
{
	std::vector<std::string> file_content;

	std::ifstream fileIn(filename);

	if(!fileIn)
	{
		this->_error_stack.push(DsmError(COULD_NOT_OPEN_MSG(filename)));
	}

	//load file content
	while(!fileIn.eof())
	{
		std::string s;
		std::getline(fileIn,s);
		file_content.push_back(s);
	}

	//parse through assets_package
	


	
}

d_ptr<Node> load_shader_data(std::string filename)
{

}
d_ptr<Node> load_shader_extension(std::string filename)
{

}

}