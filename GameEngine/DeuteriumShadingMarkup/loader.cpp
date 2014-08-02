#include "loader.h"
#define COULD_NOT_OPEN_MSG(X) "Could not open file " + X + "."
#include "shader_node.h"
namespace dsm 
{
Loader::Loader(void)
{
}


Loader::~Loader(void)
{
}

d_ptr<RenderPipe> Loader::load_rendering_pipeline(std::string render_pipe_filename, std::string render_assets_package_filename)
{
	d_ptr<RenderPipe> render_pipe(new RenderPipe());

	std::vector<d_ptr<Node> > ra_package_node;
	ra_package_node = load_assets_package(render_assets_package_filename);

	return render_pipe;
	
}
d_ptr<Node> load_render_pipe(std::string filename) 
{
	return d_ptr<Node>();
}

std::vector< d_ptr<Node> > Loader::load_assets_package(std::string filename)
{
	std::vector<std::string> file_content;
	std::vector< d_ptr<Node> > asset_package_node_list;

	std::ifstream fileIn(filename);

	if(!fileIn)
	{
		DsmErrorStack::get_instance().push(DsmError(COULD_NOT_OPEN_MSG(filename)));
	}

	//load file content
	while(!fileIn.eof())
	{
		std::string s;
		std::getline(fileIn,s);
		file_content.push_back(s);
	}

	//parse through assets_package
	Parser assets_package_parser(file_content,filename);

	//get relative filepaths to resources

	std::vector<Node::NodeData > relative_paths = assets_package_parser.extract_content(Node::RELATIVE);

	for(U32 i = 0; i < relative_paths.size(); ++i)
	{
		for(U32 j = 0; j < relative_paths[i]._content.size(); ++j)
		
			//load a .shader_data file
			if(relative_paths[i]._content[j].find(".shader_data") != std::string::npos)
			{
				
				std::vector<d_ptr<Node>> shader_data_nodes = this->load_shader_data(relative_paths[i]._content[j]);

				//load in all shader, pass and technique nodes in the parse .shader_data file
				for(int k = 0; k < shader_data_nodes.size(); ++k)
				{
					asset_package_node_list.push_back(shader_data_nodes[k]);
				}
				
			}

			//load a .shader_extension file
			//TODO
		}
		


	//get absolute filepaths to resources
	std::vector<Node::NodeData > absolute_paths = assets_package_parser.extract_content(Node::ABSOLUTE);

	return asset_package_node_list;
	
}

std::vector<d_ptr<Node>> Loader::load_shader_data(std::string filename)
{
	Parser::trim(filename);
	Node::NodeData node_data;
	node_data._filename = filename;
	std::vector< d_ptr<Node> > shader_node_list;

	std::ifstream fileIn(filename);

	if(!fileIn)
	{
		DsmErrorStack::get_instance().push(DsmError(COULD_NOT_OPEN_MSG(filename)));
		return std::vector<d_ptr<Node> >();
	}

	//load file content
	while(!fileIn.eof())
	{
		std::string s;
		std::getline(fileIn,s);
		node_data._content.push_back(s);
	}

	//parse through assets_package
	Parser shader_parser(node_data._content,node_data._filename);

	std::vector<Node::NodeData> extracted_shader_node_data_list= shader_parser.extract_content(Node::SHADER);

	for(int i = 0; i < extracted_shader_node_data_list.size(); ++i)
	{
		d_ptr<Node> shader_node_ptr(new ShaderNode);
		if(shader_node_ptr->load_content(extracted_shader_node_data_list[i]))
			shader_node_list.push_back(shader_node_ptr);
		shader_node_ptr.clear();
	}
	

	return shader_node_list;

}

d_ptr<Node> Loader::load_shader_extension(std::string filename)
{
	return d_ptr<Node>();
}

}