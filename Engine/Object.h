#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <algorithm>
#include <string>

#include "Component.h"

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Transform.h"

using namespace glm;
using namespace std;


class Object {
public:
    Object(Window& window);
    Transform* transform;
    void Initialize(Mesh* mesh, Shader* shader);
    void Update();
    void LateUpdate();

    void setPivot(vec3 pos);
    vec3 getPivot() const;

    // Component management
    template <typename T>
    void AddComponent(T* component);

    template <typename T>
    void RemoveComponent();

    template <typename T>
    T* GetComponent();

    template <typename T>
    bool IsContainComponent();

    string getName() { return objectName; }
    void setName(string newName) { objectName = newName; }

    void Destroy();

    ~Object();

private:
    vector<Component*> components;
    Mesh* objectMesh;
    Shader* objectShader;
    GLuint model;
    GLuint projection;
    mat4 modelMatrix;
    mat4 projectionMatrix;
    vec3 pivotPoint;
    string objectName;
};
// Component management
template <typename T>
void Object::AddComponent(T* component) {
    if (IsContainComponent<T>())
        return;

    Component* castedComponent = dynamic_cast<Component*>(component);
    castedComponent->Initialize(this);
    components.push_back(castedComponent);
}

template <typename T>
void Object::RemoveComponent() {
    if (!IsContainComponent<T>())
        return;

    auto it = std::remove_if(components.begin(), components.end(), [](Component* comp) {
        return dynamic_cast<T*>(comp) != nullptr;
        });

    components.erase(it, components.end());
}

template <typename T>
T* Object::GetComponent() {
    if (!IsContainComponent<T>())
        return nullptr;

    for (Component* comp : components) {
        if (T* castedComp = dynamic_cast<T*>(comp)) {
            // Tip güvenliði kontrolü için static_cast kullanýlabilir,
            // ancak dynamic_cast'in sunduðu avantajlar kaybolabilir.
            return static_cast<T*>(castedComp);
        }
    }

    return nullptr;
}

template <typename T>
bool Object::IsContainComponent() {
    for (Component* comp : components) {
        if (dynamic_cast<T*>(comp) != nullptr) {
            return true;
        }
    }
    return false;
}
