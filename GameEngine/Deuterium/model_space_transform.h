#pragma once
#include "deuterium_math.h"
namespace deuterium
{
class ModelTransform
{
public:
	ModelTransform(void);
	~ModelTransform(void);

	static void translate(Mat4x4& matrix, Vec3f translation_vector);
	static void rotate(Mat4x4 & matrix, Vec3f rotation_vector);
	static void	scale(Mat4x4& matrix, Vec3f scale_vector);

};

}