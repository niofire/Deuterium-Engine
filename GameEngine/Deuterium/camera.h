#pragma once
#include "math.h"
#include "global_data.h"

namespace deuterium
{
class Camera
	{
	public:
		//------------------------------------------------------------
		//					structure declaration
		//------------------------------------------------------------
		struct CameraData
		{
			CameraData()
			{
				_spherical_camera_position	= Vec3f(0,0,1);
				_camera_target_position	= Vec3f(0,0,0);
				_up_direction		= Vec3f(0,1,0);
			}
			Vec3f	_spherical_camera_position;
			Vec3f	_camera_target_position;
			Vec3f	_up_direction;
			char*	_name;
		};

		//------------------------------------------------------------
		//					constructor / destructor
		//------------------------------------------------------------
		Camera(Vec3f initialCameraDirection, Vec3f initialCameraTarget, Vec3f upDirection);
		Camera();
		~Camera(void);

		//------------------------------------------------------------
		//					core camera functions
		//------------------------------------------------------------
		void				rotate_camera_orientation(float x, float y, float z);
		void				rotate_camera_orientation(Vec3f);
		void				translate_camera_target(float x, float y, float z);
		void				translate_camera_target(Vec3f);
		void				set_camera_target(float x, float y, float z);
		void				set_camera_target(Vec3f);
		void				set_camera_orientation(float x, float y, float z);
		void				set_camera_orientation(Vec3f);
		void				reset_camera_position();
		void				update_lookat_matrix();



		//------------------------------------------------------------
		//					Accessors / mutators
		//------------------------------------------------------------

		const Vec3f			spherical_camera_position() { return _camera_data._spherical_camera_position;}
		const Vec3f			camera_target_position()	 { return _camera_data._camera_target_position;}
		const Vec3f			up_direction()	 { return _camera_data._up_direction;}
		Mat4x4				camera_lookat_matrix() { return _lookat_matrix;}
		const char*			name();
		void				set_name(char* i_CameraName);

	private:
		void				resolve_up_direction();
		Vec3f				euclidean_camera_position();
		CameraData			_camera_data;
		Mat4x4				_lookat_matrix;
	};
}