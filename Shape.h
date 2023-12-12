#pragma once

#include <GL/glew.h>
#include <glm/vec3.hpp>
using namespace glm;

class Shape
{
public:
	Shape(GLfloat* vertices, unsigned int* indices, unsigned int amountOfVertices, unsigned int amountOfIndices);

	GLfloat* getVertices() { return vertices; };
	unsigned int* getIndices() { return indices; };
	unsigned int getAmofVert() { return amountOfVertices; };
	unsigned int getAmofIndi() { return amountOfIndices; };

	vec3 calculateCenterPivot();  


protected:
	GLfloat* vertices;
	unsigned int* indices;
	unsigned int amountOfVertices;
	unsigned int amountOfIndices;

};
