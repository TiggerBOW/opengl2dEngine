#include "Rectangle.h"

Rectangle::Rectangle(float width, float height)
    : Shape(nullptr, nullptr, 0, 0)  // Shape sýnýfýnýn yapýcý metodunu çaðýrýn
{
    this->width = width;
    this->height = height;


    // Geniþlik ve yükseklik ayarlarý
    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;

    vertices = new GLfloat[12]{
        -halfWidth, halfHeight, -10.0f,
        -halfWidth, -halfHeight, -10.0f,
        halfWidth, -halfHeight, -10.0f,
        halfWidth, halfHeight, -10.0f
    };

    indices = new unsigned int[6] {0, 1, 2, 2, 3, 0};

    amountOfVertices = 12;
    amountOfIndices = 6;

    //Min ve max x,y deðerleri set edilir
    minX = -halfWidth;
    maxX = halfWidth;
    minY = -halfHeight;
    maxY = halfHeight;
}
