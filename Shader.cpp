#include "Shader.h"

#include <fstream>
#include <iostream>
using namespace std;
Shader::Shader(vec4 color) {
    shaderID = 0;
    uniformModel = 0;
    uniformProjection = 0;
    this->color = color;
}

void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode) {
    compileShader(vertexCode, fragmentCode);
}
void Shader::CreateFromFiles(const char* vertexLoc, const char* fragmentLoc) {
    string vertexString = ReadFile(vertexLoc);
    string fragmentString = ReadFile(fragmentLoc);
    const char* vertexCode = vertexString.c_str();
    const char* fragmentCode = fragmentString.c_str();

    compileShader(vertexCode, fragmentCode);
}
string Shader::ReadFile(const char* fileLoc) {
    string content;
    fstream fileStream(fileLoc, ios::in);

    if (!fileStream.is_open()) {
        printf("Dosya açýlamadý %s", fileLoc);
        return "";
    }

    string line = "";
    while (!fileStream.eof()) {
        getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

void Shader::compileShader(const char* vertexCode, const char* fragmentCode) {
    shaderID = glCreateProgram();

    if (!shaderID) {
        printf("Shader oluþturulamadý!");
        return;
    }

    addShader(shaderID, vertexCode, GL_VERTEX_SHADER);
    addShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar elog[1024] = { 0 };

    glLinkProgram(shaderID);
    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shaderID, sizeof(elog), NULL, elog);
        printf("Program link edilirken hata oldu : '%s'\n", elog);
        return;
    }

    glValidateProgram(shaderID);
    glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shaderID, sizeof(elog), NULL, elog);
        printf("Program validate edilirken hata oldu : '%s'\n", elog);
        return;
    }


    uniformModel = glGetUniformLocation(shaderID, "model");
    uniformProjection = glGetUniformLocation(shaderID, "projection");
}

GLuint Shader::GetProjectionLocation() {
    return uniformProjection;
}
GLuint Shader::GetModelLocation() {
    return uniformModel;
}
void Shader::UseShader() {
    glUseProgram(shaderID);
    changeColor(color);
}
void Shader::ClearShader() {
    if (shaderID != 0) {
        glDeleteProgram(shaderID);
        shaderID = 0;
    }

    uniformModel = 0;
    uniformProjection = 0;
}
void Shader::addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {
    GLuint theShader = glCreateShader(shaderType);

    const GLchar* theCode[1];
    theCode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);

    GLint result = 0;
    GLchar elog[1024] = { 0 };

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result) {
        glGetShaderInfoLog(theShader, sizeof(elog), NULL, elog);
        printf("Shader compile edilirken hata oluþtu : '%s'\n", elog);
        return;
    }

    glAttachShader(theProgram, theShader);
}
void Shader::changeColor(vec4 newColor) {
    GLint colorLocation = glGetUniformLocation(shaderID,"modelColor");
    glUniform4f(colorLocation, newColor.x, newColor.y, newColor.z, newColor.w); // r, g, b, a: Kýrmýzý, yeþil, mavi ve alfa bileþenleri
}
Shader::~Shader() {
    ClearShader();
}