#include "shader_node.h"
#include "name_node.h"
#include "include_node.h"
#include "parser.h"
#include "type_node.h"
#include "uniform_buffer_node.h"
#define DSM_FILENAME_NUMBER_ERROR(filename,line_number) "File \"" + filename + "\" at line " + line_number + ":"
namespace dsm
{

	ShaderNode::~ShaderNode()
	{

	}

	bool ShaderNode::load_content(NodeData& data)
	{
		//fetch the file name witholding the shader node
		this->_node_data._filename = data._filename;

		//get the shader node starting index
		this->_node_data._content_starting_index = data._content_starting_index;

		//get the content
		this->_node_data._content = data._content;

		//parse through shader content
		Parser shader_parser(_node_data._content,_node_data._filename);
		
		//node pointer which will be reused for each shader child nodes (name, source, etc..)		
		d_ptr<Node> node;

		std::vector<Node::NodeData> extracted_node_data_list;

		//premade error handling string
		std::string filename_number_err = DSM_FILENAME_NUMBER_ERROR(_node_data._filename,("" + _node_data._content_starting_index));


		//---------------------------------------------------------
		//			Name Node
		//---------------------------------------------------------
		node.alloc(new NameNode());
		extracted_node_data_list = shader_parser.extract_content(NAME); //PROBLEM IS HERE, RETURNS WHOLE SHADER CONTENT, NOT ONLY NAME CONTENT
		
		
		//check if a single name node is present in the shader node
		if(extracted_node_data_list.size() == 0)
		{
			DsmErrorStack::get_instance().push(DsmError(filename_number_err + "No Shader name entered."));
			return false;
			
		}
		if(extracted_node_data_list.size() > 1)
		{
			DsmErrorStack::get_instance().push(DsmError(filename_number_err + "More than one shader name entered!"));
			return false;
		}

		node->load_content(extracted_node_data_list[0]);
		this->add_child(node);

		//---------------------------------------------------------
		//			Include Node
		//---------------------------------------------------------
		node.alloc(new IncludeNode);
		extracted_node_data_list = shader_parser.extract_content(INCLUDE);

		for(int i = 0; i < extracted_node_data_list.size(); ++i)
		{
			if(node->load_content(extracted_node_data_list[i]));
				this->add_child(node);
		}

		//---------------------------------------------------------
		//			uniform_buffer Node
		//---------------------------------------------------------
		node.alloc(new UniformBufferNode);
		extracted_node_data_list = shader_parser.extract_content(UNIFORM_BUFFER);

		for(int i = 0; i < extracted_node_data_list.size(); ++i)
		{
			if(node->load_content(extracted_node_data_list[i]))
				this->add_child(node);
		}

		//---------------------------------------------------------
		//			type Node
		//---------------------------------------------------------
		node.alloc(new TypeNode());
		extracted_node_data_list = shader_parser.extract_content(TYPE); //PROBLEM IS HERE, RETURNS WHOLE SHADER CONTENT, NOT ONLY NAME CONTENT
		
		
		//check if a single name node is present in the shader node
		if(extracted_node_data_list.size() == 0)
		{
			DsmErrorStack::get_instance().push(DsmError(DSM_ERROR_MSG(
				_node_data._filename,(""+_node_data._content_starting_index),"No shader type detected.")));
			return false;
			
		}
		if(extracted_node_data_list.size() > 1)
		{
			DsmErrorStack::get_instance().push(DsmError(DSM_ERROR_MSG(
				_node_data._filename,(""+_node_data._content_starting_index),"A shader can only have one type.")));
			return false;
		}

		node->load_content(extracted_node_data_list[0]);
		this->add_child(node);

		//---------------------------------------------------------
		//			Source Node
		//---------------------------------------------------------


	}

}
