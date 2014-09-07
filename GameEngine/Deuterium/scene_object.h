#pragma once
#include "d_ptr.h"
#include "mesh.h"
namespace deuterium
{
	
class SceneObject
{
public:
	SceneObject(void);
	~SceneObject(void);


	//-------------------------------------------
	//			World positioning functions
	//-------------------------------------------
	//returns the current position of the object in world space
	const Vec3f& get_world_pos() { return Vec3f(_model_to_world[3][0],_model_to_world[3][1],_model_to_world[3][2]);}
	
	//translate the current position in world space coordinate
	void translate(const Vec3f& v) { _model_to_world[3] += Vec4f(v,0);}

	//set the current position in world space coordinates
	void set_position(const Vec3f& v) { _model_to_world[3] = Vec4f(v,0);}


	//--------------------------------------------
	//			Rendering function
	//--------------------------------------------




private:
	dPtr<Mesh> _mesh;
	dPtr<Texture> _diffuse_texture;
	
	Mat4x4 _model_to_world;
};

}