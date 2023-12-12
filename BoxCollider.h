#pragma once

#include "Component.h"

class BoxCollider : public Component
{
public:
	BoxCollider(float width, float height);
	void Update() override;
	void LateUpdate() override;

private:
	float boxWidth;
	float boxHeight;
};

