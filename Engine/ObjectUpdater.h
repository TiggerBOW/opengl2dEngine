#pragma once

#include "Object.h"
#include <vector>

class ObjectUpdater
{
public:
	ObjectUpdater();
	static ObjectUpdater* instance;

	void addObject(Object* object);
	void removeObject(Object* object);
	void UpdateObjects();
	void LateUpdateObjects();

private:
	vector<Object*> objects;
};

