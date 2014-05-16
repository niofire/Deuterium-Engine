#pragma once
#include"game_core.h"
#include "global_data.h"
#include "texture.h"
#include "shader_parameter_DA.h"
class ClientGameCore : public deuterium::GameCore
{
public:
	ClientGameCore(void);
	~ClientGameCore(void);
	 
	bool init();
	void reset();
	void exit();
	void render();
	void update();
	void on_event();

private:
	//Test variables
	U32 _shader_handle;
	U32 _mesh_handle;
	deuterium::Camera cam;
	deuterium::Texture	_texture;

	deuterium::ShaderParameterDA plane_par;
	deuterium::ShaderParameterDA obj_par;

};

