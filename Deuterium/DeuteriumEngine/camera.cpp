#include "camera.h"
#include <iostream>

namespace deuterium
{
Camera::Camera()
{
	reset_camera_position();
}

Camera::Camera(Vec3f i__spherical_camera_position,Vec3f i_CameraTarget, Vec3f i__up_direction)
{
	_camera_data._spherical_camera_position = i__spherical_camera_position;
	_camera_data._camera_target_position = i_CameraTarget;
	_camera_data._up_direction= i__up_direction;
}

Camera::~Camera()
{

}


//---------------------------------------------------------------------------------
//						Core Functions
//---------------------------------------------------------------------------------

void		Camera::reset_camera_position()
{
	_camera_data._spherical_camera_position	= Vec3f(90,0,15);
	_camera_data._camera_target_position	= Vec3f(0,0,0);
	_camera_data._up_direction		= Vec3f(0,1,0);
}


//---------------------------------------------------------------------------------
//						Accessor / Mutators
//---------------------------------------------------------------------------------
const char* Camera::name()
{
	return _camera_data._name;
}

void		Camera::set_name(char* i_CameraName)
{
	_camera_data._name = i_CameraName;
}


void Camera::rotate_camera_orientation(float xDegrees, float yDegrees, float z)
{
	this->_camera_data._spherical_camera_position.x += xDegrees;
	this->_camera_data._spherical_camera_position.y += yDegrees;
	this->_camera_data._spherical_camera_position.z += z;
}

void Camera::rotate_camera_orientation(Vec3f vector)
{
	this->_camera_data._spherical_camera_position.x += vector.x;
	this->_camera_data._spherical_camera_position.y += vector.y;
	this->_camera_data._spherical_camera_position.z += vector.z;
}

void Camera::translate_camera_target(float x,float y,float z)
{
	this->_camera_data._camera_target_position.x += x;
	this->_camera_data._camera_target_position.y += y;
	this->_camera_data._camera_target_position.z += z;
}

void Camera::translate_camera_target(Vec3f vector)
{
	this->_camera_data._camera_target_position.x += vector.x;
	this->_camera_data._camera_target_position.y += vector.y;
	this->_camera_data._camera_target_position.z += vector.z;
}

void Camera::set_camera_target(float x,float y, float z)
{
	this->_camera_data._camera_target_position.x = x;
	this->_camera_data._camera_target_position.y = y;
	this->_camera_data._camera_target_position.z = z;
}

void Camera::set_camera_target(Vec3f vector)
{
	this->_camera_data._camera_target_position.x = vector.x;
	this->_camera_data._camera_target_position.y = vector.y;
	this->_camera_data._camera_target_position.z = vector.z;
}

void Camera::set_camera_orientation(Vec3f vector)
{
	this->_camera_data._spherical_camera_position.x = vector.x;
	this->_camera_data._spherical_camera_position.y = vector.y;
	this->_camera_data._spherical_camera_position.z = vector.z;
}

void Camera::set_camera_orientation(float x, float y, float z)
{
	this->_camera_data._spherical_camera_position.x = x;
	this->_camera_data._spherical_camera_position.y = y;
	this->_camera_data._spherical_camera_position.z = z;
}

Vec3f Camera::euclidean_camera_position()
{
	//convert the position in spherical coordinates
	float phi = MathHelper_L::deg_to_rad(_camera_data._spherical_camera_position.x);
	float theta = MathHelper_L::deg_to_rad(_camera_data._spherical_camera_position.y + 90);
    
	//Spherical transform => 
	//x = rsin(theta)cos(phi)
	//y = rsin(theta)sin(phi)
	//z = rcos(theta)
	//Where Z is "upwards, hence interchanging y and z
    float sinTheta = sinf(theta);
    float cosTheta = cosf(theta);
    float cosPhi = cosf(phi);
    float sinPhi = sinf(phi);
    
    Vec3f dirToCamera(sinTheta * cosPhi, cosTheta, sinTheta * sinPhi);
	return (dirToCamera * _camera_data._spherical_camera_position.z) + _camera_data._camera_target_position;
}

void Camera::resolve_up_direction()
{
		//convert the position in spherical coordinates
	float phi = MathHelper_L::deg_to_rad(_camera_data._spherical_camera_position.x);
	float theta = MathHelper_L::deg_to_rad(_camera_data._spherical_camera_position.y);
    
	//Spherical transform => 
	//x = rsin(theta)cos(phi)
	//y = rsin(theta)sin(phi)
	//z = rcos(theta)
	//Where Z is "upwards, hence interchanging y and z
    float sinTheta = sinf(theta);
    float cosTheta = cosf(theta);
    float cosPhi = cosf(phi);
    float sinPhi = sinf(phi);
    
    Vec3f dirToCamera(sinTheta * cosPhi, cosTheta, sinTheta * sinPhi);
	_camera_data._up_direction =  (dirToCamera * _camera_data._spherical_camera_position.z) + _camera_data._camera_target_position;
	_camera_data._up_direction.Normalize();
}

void Camera::update_lookat_matrix()
{
	Vec3f l_CameraPosition = euclidean_camera_position();


	//Resolve the Up direction
	resolve_up_direction();

	
	
	//Get the camera direction, Target - position
	Vec3f l_CameraDirection = (_camera_data._camera_target_position - l_CameraPosition).GetNormalized();

	//Get right direction, camDirection  X up
	Vec3f l_RightDirection = MathHelper_L::cross_product(l_CameraDirection, _camera_data._up_direction).GetNormalized();

	//Get the up direction, camDirection X right
	Vec3f l_up_direction =  -(MathHelper_L::cross_product(l_CameraDirection,l_RightDirection)).GetNormalized();


	//Fill lookat matrix
	_lookat_matrix[0] = Vec4f(l_RightDirection,0);
	_lookat_matrix[1] = Vec4f(l_up_direction,0);
	_lookat_matrix[2] = Vec4f(-l_CameraDirection,0);
	_lookat_matrix[3] = Vec4f(0,0,0,1);
	_lookat_matrix.Transpose();

	//_lookat_matrix.SetIdentity();
	MathHelper_L::fast_translate(_lookat_matrix,-l_CameraPosition);
}
}