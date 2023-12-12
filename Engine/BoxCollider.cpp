#include "BoxCollider.h"

#include "Object.h"

BoxCollider::BoxCollider(float width, float height) : boxWidth(width), boxHeight(height){}

void BoxCollider::Update() {
	object->transform->calculateBoundingBox(boxWidth, boxHeight);
}
void BoxCollider::LateUpdate() {

}