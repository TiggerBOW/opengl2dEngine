// Transform.h
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Rectangle.h"

using namespace glm;

class Transform {
public:
    Transform(mat4* modelMatrix, vec3 pivotPoint = vec3(0.0f));
    void calculateTrs();
    void translate(vec3 position);
    void rotate(float angle, vec3 axis);
    void scale(vec3 axis);
    void resetTransformation();

    vec3 getPosition();
    void setPosition(vec3 pos);

    // Yeni fonksiyonlar
    void calculateBoundingBox(float width, float height);
    float getMinX();
    float getMaxX();
    float getMinY();
    float getMaxY();

private:
    mat4* modelMatrix;
    mat4 initialModelMatrix;
    mat4 translateMatrix;
    mat4 rotationMatrix;
    mat4 scaleMatrix;
    vec3 pivotPoint;  // Pivot noktasý eklendi
    float minX, maxX, minY, maxY; // Min-max deðerleri eklendi
};
