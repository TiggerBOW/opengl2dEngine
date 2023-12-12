#include "Object.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ObjectUpdater.h"

Object::Object(Window& window) {
    //identity matrix olarak baþlatýldý
    modelMatrix = glm::mat4(1.0f);
    //Ortografik projeksiyon baþlatýldý
    projectionMatrix = glm::perspective(45.0f, (GLfloat)window.getBufferWidth() / (GLfloat)window.getBufferHeight(), 0.1f, 100.0f);
    //Transform
    transform = new Transform(&modelMatrix, getPivot());

    objectName = "";

    model = 0;
    projection = 0;

    ObjectUpdater::instance->addObject(this);
}

void Object::Initialize(Mesh* mesh, Shader* shader) {
    objectMesh = mesh;
    objectShader = shader;
}

void Object::Update() {
    objectShader->UseShader();
    model = objectShader->GetModelLocation();
    projection = objectShader->GetProjectionLocation();

    //Components bilgileri güncellenir.
    for (int i = 0; i < components.size(); i++) {
        components[i]->Update();
    }

    //Transform bilgileri güncellenir.
    transform->calculateTrs();

    glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    objectMesh->RenderMesh();
}
void Object::LateUpdate() {
    //Components bilgileri güncellenir.
    for (int i = 0; i < components.size(); i++) {
        components[i]->LateUpdate();
    }
}
void Object::setPivot(vec3 pos) {
    pivotPoint = pos;
}

vec3 Object::getPivot() const {
    return pivotPoint;
}
void Object::Destroy() {
    objectMesh->ClearMesh();
    objectShader->ClearShader();
    ObjectUpdater::instance->removeObject(this);
}
Object::~Object() {
    objectMesh->ClearMesh();
    objectShader->ClearShader();
}

