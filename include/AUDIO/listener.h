#ifndef LISTENER_H
#define LISTENER_H

#include <AL/al.h>
#include <AL/alc.h>
#include <mutex>
#include <array>


class Listener {
public:
    Listener();
    ~Listener() = default;

    void setPosition(float x, float y, float z);
    void setVelocity(float x, float y, float z);
    void setOrientation(float atX, float atY, float atZ, float upX, float upY, float upZ);

    std::array<float, 3> getPosition() const;
    std::array<float, 3> getVelocity() const;
    std::array<float, 6> getOrientation() const;

    float posX, posY, posZ;
    float velX, velY, velZ;
    float oriAtX, oriAtY, oriAtZ;
    float oriUpX, oriUpY, oriUpZ;

private:
    mutable std::mutex mtx;

};

#endif // LISTENER_H
