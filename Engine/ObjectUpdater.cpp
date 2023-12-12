#include "ObjectUpdater.h"

ObjectUpdater* ObjectUpdater::instance;

ObjectUpdater::ObjectUpdater() {
    instance = this;
}
void ObjectUpdater::addObject(Object* object) {
    objects.push_back(object);
}

void ObjectUpdater::removeObject(Object* object) {
    // object'ý vector'den kaldýrma
    auto it = std::find(objects.begin(), objects.end(), object);
    if (it != objects.end()) {
        objects.erase(it);
    }
}

void ObjectUpdater::UpdateObjects() {
    // Tüm nesneleri güncelle
    for (Object* object : objects) {
        object->Update();
    }
}

void ObjectUpdater::LateUpdateObjects() {
    // Tüm nesneleri LateUpdate et
    for (Object* object : objects) {
        object->LateUpdate();
    }
}
