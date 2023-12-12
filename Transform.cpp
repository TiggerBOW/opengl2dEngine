// Transform.cpp
#include "Transform.h"


Transform::Transform(mat4* modelMatrix, vec3 pivotPoint) {
    this->modelMatrix = modelMatrix;
    this->initialModelMatrix = *modelMatrix;
    this->pivotPoint = pivotPoint;
    translateMatrix = mat4(1.0f);
    rotationMatrix = mat4(1.0f);
    scaleMatrix = mat4(1.0f);
}

void Transform::calculateTrs() {
    mat4 pivotTranslate = glm::translate(mat4(1.0f), pivotPoint);
    mat4 pivotTranslateInv = glm::translate(mat4(1.0f), -pivotPoint);
    *modelMatrix = pivotTranslate * translateMatrix * rotationMatrix * scaleMatrix * pivotTranslateInv * initialModelMatrix;

}

vec3 Transform::getPosition() {
    return glm::vec3((*modelMatrix)[3]);
}

void Transform::translate(vec3 position) {
    translateMatrix = glm::translate(mat4(1.0f), position);
    calculateTrs();
}

void Transform::rotate(float angle, vec3 axis) {
    rotationMatrix = glm::rotate(mat4(1.0f), glm::radians(angle), axis);
    calculateTrs();
}

void Transform::scale(vec3 axis) {
    scaleMatrix = glm::scale(mat4(1.0f), axis);
    calculateTrs();
}

void Transform::resetTransformation() {
    translateMatrix = mat4(1.0f);
    rotationMatrix = mat4(1.0f);
    scaleMatrix = mat4(1.0f);
}

void Transform::calculateBoundingBox(float width, float height) {
    vec3 pivot = pivotPoint;

    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;

    vec4 topLeft = initialModelMatrix * vec4(pivot - vec3(halfWidth, halfHeight, 0.0f), 1.0f);
    vec4 topRight = initialModelMatrix * vec4(pivot + vec3(halfWidth, halfHeight, 0.0f), 1.0f);
    vec4 bottomLeft = initialModelMatrix * vec4(pivot - vec3(halfWidth, -halfHeight, 0.0f), 1.0f);
    vec4 bottomRight = initialModelMatrix * vec4(pivot + vec3(halfWidth, -halfHeight, 0.0f), 1.0f);

    topLeft = (*modelMatrix) * topLeft;
    topRight = (*modelMatrix) * topRight;
    bottomLeft = (*modelMatrix) * bottomLeft;
    bottomRight = (*modelMatrix) * bottomRight;

    vec3 minPoint = vec3(min(topLeft.x, min(topRight.x, min(bottomLeft.x, bottomRight.x))),
        min(topLeft.y, min(topRight.y, min(bottomLeft.y, bottomRight.y))),
        min(topLeft.z, min(topRight.z, min(bottomLeft.z, bottomRight.z))));

    vec3 maxPoint = vec3(max(topLeft.x, max(topRight.x, max(bottomLeft.x, bottomRight.x))),
        max(topLeft.y, max(topRight.y, max(bottomLeft.y, bottomRight.y))),
        max(topLeft.z, max(topRight.z, max(bottomLeft.z, bottomRight.z))));

    minX = minPoint.x;
    maxX = maxPoint.x;
    minY = minPoint.y;
    maxY = maxPoint.y;
}

float Transform::getMinX() {
    return minX;
}

float Transform::getMaxX() {
    return maxX;
}

float Transform::getMinY() {
    return minY;
}

float Transform::getMaxY() {
    return maxY;
}
