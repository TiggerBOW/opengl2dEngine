#include "Shape.h"

Shape::Shape(GLfloat* vertices, unsigned int* indices, unsigned int amountOfVertices, unsigned int amountOfIndices) {

    this->vertices = vertices;
    this->indices = indices;
    this->amountOfVertices = amountOfVertices;
    this->amountOfIndices = amountOfIndices;

    calculateCenterPivot();
}

vec3 Shape::calculateCenterPivot() {
    // Vertices'larýn ortalamasýný alarak tam merkezi bir pivot ayarla
    vec3 sum(0.0f);
    for (unsigned int i = 0; i < amountOfVertices; i += 3) {
        sum += vec3(vertices[i], vertices[i + 1], vertices[i + 2]);
    }
    return sum / static_cast<float>(amountOfVertices / 3);
}
