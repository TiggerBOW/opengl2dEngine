#pragma once

#include <GL\glew.h>
#include "Shape.h"

class Mesh
{
public:
	Mesh();

	void CreateMesh(Shape& shape);
	void RenderMesh();
	void ClearMesh();
	~Mesh();

private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
};

