#pragma once

#include <glm/vec3.hpp>

#include "PhysicObject.h"

using namespace glm;

class LinearMovement
{
public:
	static void Force(PhysicObject* obj, vec3 direction, float amount);
};

