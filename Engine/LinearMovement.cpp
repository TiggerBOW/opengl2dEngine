#include "LinearMovement.h"
#include "Time.h"

void LinearMovement::Force(PhysicObject* obj, vec3 direction, float amount) {
	float accelertion = amount / obj->mass;
	obj->velocity += direction * accelertion * Time::deltaTime;
}