#include "Input.h"
#include <iostream>

bool Input::keyPressing(int key, GLFWwindow* window) {
    bool x = (glfwGetKey(window, key) == GLFW_PRESS);
    return x;
}

bool Input::keyPressed(int key, GLFWwindow* window) {
    static bool prevState = false; // �nceki durumu tutmak i�in bir de�i�ken

    bool currentState = (glfwGetKey(window, key) == GLFW_PRESS);

    // E�er tu�a bas�ld�ysa ve �nceki durum bas�lmam��sa
    if (currentState && !prevState) {
        std::cout << "Tu�a bas�ld�: " << key << std::endl;
        prevState = true; // Durumu g�ncelle
        return true;
    }
    else if (!currentState) {
        prevState = false; // Tu� b�rak�ld���nda durumu g�ncelle
    }

    return false;
}

bool Input::keyPressUp(int key, GLFWwindow* window) {
    // GLFW_RELEASE durumu tu�un b�rak�ld���n� g�sterir
    return (glfwGetKey(window, key) == GLFW_RELEASE);
}
