#include "Window.h"
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <iostream>

#include <cmath>
#include <glm/vec4.hpp>

#include "Object.h"
#include "Shape.h"
#include "Rectangle.h"
#include "LinearMovement.h"
#include "PhysicObject.h"
#include "AABBCollision.h"
#include "BoxCollider.h"
#include "Component.h"

#include "Time.h"
#include "Input.h"
#include "ObjectUpdater.h"

Object* createCoin(Window *window,vec3 pos,Shader* coinShader) {
    Rectangle* coinRect = new Rectangle(0.5f, 0.5f);
    Mesh* coinMesh = new Mesh();
    coinMesh->CreateMesh(*coinRect);

    Object* coinObj = new Object(*window);
    coinObj->Initialize(coinMesh, coinShader);
    coinObj->setPivot(coinRect->calculateCenterPivot());
    BoxCollider* coinCollider = new BoxCollider(coinRect->getWidth(), coinRect->getHeight());
    coinObj->AddComponent<BoxCollider>(coinCollider);
    coinObj->setName("coin");
    coinObj->transform->translate(pos);

    return coinObj;
}
int main()
{
    Window window(800, 600, "Game");
    window.Initialize();

    ObjectUpdater* updater = new ObjectUpdater();



    Rectangle* rect = new Rectangle(1.0f, 1.0f);
    
    Mesh* squareMesh = new Mesh();
    squareMesh->CreateMesh(*rect);

    Shader* shader = new Shader(vec4(1,1,1,1));
    shader->CreateFromFiles("Shaders/shader.vert", "Shaders/shader.frag");

    Object* object = new Object(window);
    object->Initialize(squareMesh, shader);
    object->setPivot(rect->calculateCenterPivot());
    PhysicObject* phyObj = new PhysicObject(5);
    object->AddComponent(phyObj);
    BoxCollider* collider0 = new BoxCollider(rect->getWidth(),rect->getHeight());
    object->AddComponent<BoxCollider>(collider0);


    Shader* coinShader = new Shader(vec4(0.855f, 0.657f, 0.125f, 1.0f));
    coinShader->CreateFromFiles("Shaders/shader.vert", "Shaders/shader.frag");
    Object* coin1 = createCoin(&window,vec3(5,1,0), coinShader);


    Time* time = new Time();

    AABBCollision::addCollideObj(object);
    AABBCollision::addCollideObj(coin1);


    vec3 moveDirection;
    float moveSpeed = 30.0f;
    float dashPower = 500.0f;
    float maxSpeed = 4.0f;

    while (!window.getShouldClose()) {
        glfwPollEvents();
        window.clearWindow(glm::vec4(0, 0, 0, 1));

        time->setFps(60);

        updater->UpdateObjects();
        

        if (Input::keyPressing(GLFW_KEY_A, window.getWindow())) {
            moveDirection.x = -1;
        }
        if (Input::keyPressing(GLFW_KEY_D, window.getWindow())) {
            moveDirection.x = 1;
        }
        if (Input::keyPressing(GLFW_KEY_W, window.getWindow())) {
            moveDirection.y = 1;
        }
        if (Input::keyPressing(GLFW_KEY_S, window.getWindow())) {
            moveDirection.y = -1;
        }
        if (Input::keyPressUp(GLFW_KEY_A,window.getWindow()) && Input::keyPressUp(GLFW_KEY_D, window.getWindow()) &&
            Input::keyPressUp(GLFW_KEY_W,window.getWindow()) && Input::keyPressUp(GLFW_KEY_S, window.getWindow())) {
            moveDirection = vec3(0, 0, 0);
        }

        LinearMovement::Force(phyObj, moveDirection, moveSpeed);
        LinearMovement::Force(phyObj, -phyObj->velocity, moveSpeed / 2);

        if (length(phyObj->velocity) >= maxSpeed) {
            phyObj->velocity = moveDirection * maxSpeed;
        }
        
        Object* otherObj;
        if (AABBCollision::IsColliding(object,otherObj)) {
            if (otherObj->getName() == "coin") {
                otherObj->Destroy();
            }
        }

        updater->LateUpdateObjects();


        window.swapBuffers();
    }
}
