#pragma once

class Object;

class Component
{
public:
	void Initialize(Object* object);
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;

protected:
	Object* object;
};

