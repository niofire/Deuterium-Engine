#include "model_space_transform.h"

namespace deuterium
{
ModelTransform::ModelTransform(void)
{
}


ModelTransform::~ModelTransform(void)
{
}

void ModelTransform::translate(Mat4x4& matrix, Vec3f translation_vector)
{
	matrix[3][0] = translation_vector[0];
	matrix[3][1] = translation_vector[1];
	matrix[3][2] = translation_vector[2];
}

void ModelTransform::rotate(Mat4x4 & matrix, Vec3f rotation_vector)
{

}

void ModelTransform::scale(Mat4x4& matrix, Vec3f scale_vector)
{
	for(int i = 0; i < 3; ++i)
	{
		matrix[i][i] *= scale_vector[i];
	}
}
}