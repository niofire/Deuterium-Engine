#pragma once

#include "deuterium_math.h"

namespace deuterium
{

class node
{
public:
	node(void);
	~node(void);

	Mat4x4 _model_to_world_transform;
};

}
