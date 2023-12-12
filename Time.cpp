#include "Time.h"


float Time::deltaTime;

Time::Time() {
    lastTime = glfwGetTime();
}
void Time::setFps(float fps) {

    deltaTime = 1 / fps;
    targetFrameTime = deltaTime;

    // Zaman geçen süreyi hesapla
    double currentTime = glfwGetTime();
    double deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    // FPS sýnýrlamasý
    if (deltaTime < targetFrameTime) {
        double sleepTime = targetFrameTime - deltaTime;
        // Sleep fonksiyonu yerine busy wait (meþgul bekleyiþ) kullanabilirsiniz
        while ((glfwGetTime() - currentTime) < sleepTime) {}
    }
}