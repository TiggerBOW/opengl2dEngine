#pragma once

#include <glm/vec3.hpp>

#include "Object.h" 
#include "Component.h"

using namespace glm;

class PhysicObject : public Component
{
public:
	PhysicObject(float mass);
	void move();
	vec3 velocity;
	float mass;

	void Update() override;
	void LateUpdate() override;
};

