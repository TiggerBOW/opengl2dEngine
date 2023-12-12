#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <glm/vec4.hpp>

using namespace std;
using namespace glm;

class Shader
{
public:
	Shader(vec4 color);

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexLoc, const char* fragmentLoc);

	string ReadFile(const char* fileLoc);

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();

	void UseShader();
	void ClearShader();

	void changeColor(vec4 newColor);


	~Shader();
private:
	GLuint shaderID, uniformProjection, uniformModel;

	void compileShader(const char* vertexCode, const char* fragmentCode);
	void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);

	vec4 color;
};

