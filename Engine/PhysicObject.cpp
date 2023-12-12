#include "PhysicObject.h"
#include "Time.h"


PhysicObject::PhysicObject(float mass) {
	this->mass = mass;
}
void PhysicObject::move() {
	vec3 newPos = object->transform->getPosition() + (velocity * Time::deltaTime);
	object->transform->translate(newPos);

}
void PhysicObject::Update(){

}
void PhysicObject::LateUpdate() {
	move();
}
