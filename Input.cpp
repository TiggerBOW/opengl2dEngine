#include "Input.h"
#include <iostream>

bool Input::keyPressing(int key, GLFWwindow* window) {
    bool x = (glfwGetKey(window, key) == GLFW_PRESS);
    return x;
}

bool Input::keyPressed(int key, GLFWwindow* window) {
    static bool prevState = false; // Önceki durumu tutmak için bir deðiþken

    bool currentState = (glfwGetKey(window, key) == GLFW_PRESS);

    // Eðer tuþa basýldýysa ve önceki durum basýlmamýþsa
    if (currentState && !prevState) {
        std::cout << "Tuþa basýldý: " << key << std::endl;
        prevState = true; // Durumu güncelle
        return true;
    }
    else if (!currentState) {
        prevState = false; // Tuþ býrakýldýðýnda durumu güncelle
    }

    return false;
}

bool Input::keyPressUp(int key, GLFWwindow* window) {
    // GLFW_RELEASE durumu tuþun býrakýldýðýný gösterir
    return (glfwGetKey(window, key) == GLFW_RELEASE);
}
