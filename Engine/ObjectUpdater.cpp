#include "ObjectUpdater.h"

ObjectUpdater* ObjectUpdater::instance;

ObjectUpdater::ObjectUpdater() {
    instance = this;
}
void ObjectUpdater::addObject(Object* object) {
    objects.push_back(object);
}

void ObjectUpdater::removeObject(Object* object) {
    // object'� vector'den kald�rma
    auto it = std::find(objects.begin(), objects.end(), object);
    if (it != objects.end()) {
        objects.erase(it);
    }
}

void ObjectUpdater::UpdateObjects() {
    // T�m nesneleri g�ncelle
    for (Object* object : objects) {
        object->Update();
    }
}

void ObjectUpdater::LateUpdateObjects() {
    // T�m nesneleri LateUpdate et
    for (Object* object : objects) {
        object->LateUpdate();
    }
}
