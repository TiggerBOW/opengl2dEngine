#pragma once

#include "Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle(float width, float height);

	float getWidth() { return width; }
	float getHeight() { return height; }

	float getMinX() { return minX; }
	float getMaxX() { return maxX; }
	float getMinY() { return minY; }
	float getMaxY() { return maxY; }

private:
	float width;
	float height;

	float minX;
	float maxX;
	float minY;
	float maxY;
};

