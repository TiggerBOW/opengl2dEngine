#include "Time.h"


float Time::deltaTime;

Time::Time() {
    lastTime = glfwGetTime();
}
void Time::setFps(float fps) {

    deltaTime = 1 / fps;
    targetFrameTime = deltaTime;

    // Zaman ge�en s�reyi hesapla
    double currentTime = glfwGetTime();
    double deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    // FPS s�n�rlamas�
    if (deltaTime < targetFrameTime) {
        double sleepTime = targetFrameTime - deltaTime;
        // Sleep fonksiyonu yerine busy wait (me�gul bekleyi�) kullanabilirsiniz
        while ((glfwGetTime() - currentTime) < sleepTime) {}
    }
}