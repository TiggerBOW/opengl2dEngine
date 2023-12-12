#include "Component.h"
#include <iostream>

void Component::Initialize(Object* object) {
	this->object = object;
	std::cout << object << "\n";
}