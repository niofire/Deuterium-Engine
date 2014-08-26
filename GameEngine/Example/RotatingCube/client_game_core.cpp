#include "client_game_core.h"
#include "model_space_transform.h"
#include "camera.h"

ClientGameCore::ClientGameCore(void)
{
}


ClientGameCore::~ClientGameCore(void)
{
}

bool ClientGameCore::init()
{
	using namespace deuterium;
	//Initializes all managers
	GameCore::init();
	g_data._mesh_manager_ptr->add_and_load_new_mesh(_mesh_handle, "Square", "Resources/Models/Square.obj");
	//TODO Redesign draw request class + processing


	return true;
}
	
	/*
	//----------------------------------------------------
	//			Load Model
	//----------------------------------------------------
	
	//
	// underlying plane
	//
	U32 plane_handle;
	g_data._mesh_manager_ptr->add_and_load_new_mesh(plane_handle,"plane","Resources/Models/Square.obj");

	//Object
		//Mesh is loaded
		g_data._mesh_manager_ptr->add_and_load_new_mesh(_mesh_handle,"Monkey","Resources/Models/Dice.obj");
	//-----------------------------------------------------
	//			Load Shader
	//-----------------------------------------------------
	g_data._shader_manager_ptr->CreateShaderFromFile(
			_shader_handle,"Example Shader","Resources/Shaders/vertexShader.glsl",
			"Resources/Shaders/fragmentShader.glsl");

	
	_texture.LoadPngTexture("Resources/Textures/monkey_t2.png");

	obj_par.update_shader_parameter_declaration(_shader_handle);
	plane_par.update_shader_parameter_declaration(_shader_handle);

	return true;
}

void ClientGameCore::reset()
{
	GameCore::reset();
}

void ClientGameCore::exit()
{
	GameCore::exit();
}

void ClientGameCore::render()
{
	//Processes draw requests
	GameCore::render();
}

void ClientGameCore::update()
{
	using namespace deuterium;
	GameCore::update();
	//deuterium::Shader s = deuterium::g_data._shader_manager_ptr->GetShader(_shader_handle);
	cam.update_lookat_matrix();
	
	
	Mat4x4 world_view_matrix = cam.to_viewspace_matrix();

	//Update plane
	//transform matrix
	Mat4x4 plane_transform;
	ModelTransform::scale(plane_transform,Vec3f(5,0.1,5));
	ModelTransform::translate(plane_transform,Vec3f(10.0,0,0));
	
	Mat4x4 proj_mat = g_data._renderer_ptr->perspective_projection_matrix(20,1,0.1,100);
	plane_par.dirty_parameter("model_world_proj",plane_transform.GetPtr());
	plane_par.dirty_parameter("world_view_proj", world_view_matrix.GetIdentity().GetPtr());
	plane_par.dirty_parameter("projection_mat",proj_mat.GetIdentity().GetPtr());

	deuterium::Mat4x4 model_proj;

	obj_par.dirty_parameter("model_world_proj",model_proj.GetIdentity().GetPtr());
	obj_par.dirty_parameter("world_view_proj", world_view_matrix.GetIdentity().GetPtr());
	obj_par.dirty_parameter("projection_mat",proj_mat.GetIdentity().GetPtr());

	
	s.bind_texture_to_sampler("texture_sampler",&_texture);
	cam.rotate_camera_orientation(deuterium::Vec3f(0.1,0.2,0.0));
	deuterium::g_data._shader_manager_ptr->GetShader(_shader_handle).bind_current_parameters();
	
	deuterium::DrawRequest* r = new deuterium::DrawRequest();
	
	r->MeshId = _mesh_handle;
	r->ShaderId = _shader_handle;
	r->IsTransparent = false;
	r->ZValue = 0;
	r->ShaderParamArray = &obj_par;
	ADD_DRAWREQUEST(r);


	DrawRequest* r2 = new DrawRequest;
	r2->MeshId = g_data._mesh_manager_ptr->mesh_data_by_name("plane")->id();
	r2->ShaderId = _shader_handle;
	r2->ZValue = 0;
	r2->ShaderParamArray = &plane_par;
	//ADD_DRAWREQUEST(r2);
	*/

void ClientGameCore::exit()
{
}

void ClientGameCore::render()
{

}

void ClientGameCore::reset()
{

}

void ClientGameCore::update()
{

}

void ClientGameCore::on_event()
{
	//Updates EventManager
	GameCore::on_event();
}
