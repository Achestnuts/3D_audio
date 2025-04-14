#include "listener.h"

Listener::Listener()
    : posX(0.0f), posY(0.0f), posZ(0.0f),
    velX(0.0f), velY(0.0f), velZ(0.0f),
    oriAtX(0.0f), oriAtY(0.0f), oriAtZ(-1.0f),  // 默认朝向负 Z 轴
    oriUpX(0.0f), oriUpY(1.0f), oriUpZ(0.0f) { // 默认 Y 轴向上
    // 初始化 OpenAL 监听器参数
    alListener3f(AL_POSITION, posX, posY, posZ);
    alListener3f(AL_VELOCITY, velX, velY, velZ);

    float orientation[] = { oriAtX, oriAtY, oriAtZ, oriUpX, oriUpY, oriUpZ };
    alListenerfv(AL_ORIENTATION, orientation);
}

void Listener::setPosition(float x, float y, float z) {
    std::lock_guard<std::mutex> lock(mtx);
    posX = x;
    posY = y;
    posZ = z;
    alListener3f(AL_POSITION, x, y, z);
}

void Listener::setVelocity(float x, float y, float z) {
    std::lock_guard<std::mutex> lock(mtx);
    velX = x;
    velY = y;
    velZ = z;
    alListener3f(AL_VELOCITY, x, y, z);
}

void Listener::setOrientation(float atX, float atY, float atZ, float upX, float upY, float upZ) {
    std::lock_guard<std::mutex> lock(mtx);
    oriAtX = atX;
    oriAtY = atY;
    oriAtZ = atZ;
    oriUpX = upX;
    oriUpY = upY;
    oriUpZ = upZ;

    float orientation[] = { atX, atY, atZ, upX, upY, upZ };
    alListenerfv(AL_ORIENTATION, orientation);
}

std::array<float, 3> Listener::getPosition() const {
    std::lock_guard<std::mutex> lock(mtx);
    return { posX, posY, posZ };
}

std::array<float, 3> Listener::getVelocity() const {
    std::lock_guard<std::mutex> lock(mtx);
    return { velX, velY, velZ };
}

std::array<float, 6> Listener::getOrientation() const {
    std::lock_guard<std::mutex> lock(mtx);
    return { oriAtX, oriAtY, oriAtZ, oriUpX, oriUpY, oriUpZ };
}
