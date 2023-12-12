#pragma once

#include "Object.h";
#include <vector>

class AABBCollision
{
public:
	static bool Intersect(Object* obj1, Object* obj2);

	static void addCollideObj(Object* object);
	static void removeColliderObj(Object* object);

	static void SolveColliders();
	static void SolveCollidersFor(Object* obj);

	static bool IsColliding(Object* obj, Object*& collidingObject);

private:
	static vector<Object*> collideObjects;
};

