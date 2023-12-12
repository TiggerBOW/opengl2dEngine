#include "AABBCollision.h"
#include "PhysicObject.h"
#include "LinearMovement.h"
#include <iostream>


std::vector<Object*> AABBCollision::collideObjects;

bool AABBCollision::Intersect(Object* obj1, Object* obj2) {
    // rect1'in sýnýrlarý
    float rect1MinX = obj1->transform->getMinX();
    float rect1MaxX = obj1->transform->getMaxX();
    float rect1MinY = obj1->transform->getMinY();
    float rect1MaxY = obj1->transform->getMaxY();

    // rect2'nin sýnýrlarý
    float rect2MinX = obj2->transform->getMinX();
    float rect2MaxX = obj2->transform->getMaxX();
    float rect2MinY = obj2->transform->getMinY();
    float rect2MaxY = obj2->transform->getMaxY();

    // X ekseninde çakýþma kontrolü
    bool overlapX = (rect1MinX <= rect2MaxX && rect1MaxX >= rect2MinX) ||
        (rect2MinX <= rect1MaxX && rect2MaxX >= rect1MinX);

    // Y ekseninde çakýþma kontrolü
    bool overlapY = (rect1MinY <= rect2MaxY && rect1MaxY >= rect2MinY) ||
        (rect2MinY <= rect1MaxY && rect2MaxY >= rect1MinY);

    // Hem X hem de Y eksenlerinde çakýþma varsa, iki dikdörtgen çakýþýyor demektir.
    return overlapX && overlapY;
}
void AABBCollision::addCollideObj(Object* obj) {
    collideObjects.push_back(obj);
}
void AABBCollision::removeColliderObj(Object* obj) {
    auto it = std::find(collideObjects.begin(), collideObjects.end(), obj);

    if (it != collideObjects.end()) {
        collideObjects.erase(it);
    }
}
bool AABBCollision::IsColliding(Object* obj, Object*& collidingObject) {
    for (Object* otherObj : collideObjects) {
        if (obj != otherObj && Intersect(obj, otherObj)) {
            collidingObject = otherObj;
            return true;
        }
    }
    collidingObject = nullptr; // Çakýþma olmadýðýnda, collidingObject'ý null olarak ayarla
    return false;
}

void AABBCollision::SolveColliders() {
    for (int i = 0; i < collideObjects.size(); i++) {
        for (int j = 0; j < collideObjects.size(); j++) {
            if (collideObjects[i] != collideObjects[j]) {
                if (Intersect(collideObjects[i], collideObjects[j])) {
                    PhysicObject* obj1 = collideObjects[i]->GetComponent<PhysicObject>();
                    PhysicObject* obj2 = collideObjects[j]->GetComponent<PhysicObject>();

                    if (obj1 != nullptr && obj2 == nullptr) {
                        vec3 dir = collideObjects[j]->transform->getPosition() - collideObjects[i]->transform->getPosition();
                        vec3 dirNormalized = normalize(dir);

                        obj1->velocity = dirNormalized * 0.005f;
                    }
                    else if (obj1 == nullptr && obj2 != nullptr) {

                        vec3 dir = collideObjects[j]->transform->getPosition() - collideObjects[i]->transform->getPosition();
                        vec3 dirNormalized = normalize(dir);

                        obj2->velocity = dirNormalized * 0.005f;

                    }
                }
            }
        }
    }

}
void AABBCollision::SolveCollidersFor(Object* obj) {
    for (int i = 0; i < collideObjects.size(); i++) {
        if (collideObjects[i] != obj) {
            if (Intersect(collideObjects[i], obj)) {
                PhysicObject* obj1 = collideObjects[i]->GetComponent<PhysicObject>();
                PhysicObject* obj2 = obj->GetComponent<PhysicObject>();

                if (obj1 != nullptr && obj2 == nullptr) {
                    vec3 dir = obj->transform->getPosition() - collideObjects[i]->transform->getPosition();
                    vec3 dirNormalized = normalize(dir);

                    obj1->velocity = dirNormalized * 0.005f;
                }
                else if (obj1 == nullptr && obj2 != nullptr) {

                    vec3 dir = obj->transform->getPosition() - collideObjects[i]->transform->getPosition();
                    vec3 dirNormalized = normalize(dir);

                    obj2->velocity = dirNormalized * 0.005f;

                }
            }
        }
    }
}


