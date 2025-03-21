#pragma once
#include <glm/fwd.hpp>
#include <glm/glm.hpp>

class Collider
{
public:
    virtual ~Collider()
    {
    }

    template <typename T>
    bool isOf() { return (dynamic_cast<T*>(this) != nullptr); }

    Collider(): transform(glm::mat4(1)), center(glm::vec3(0)), hasGravity(false), isKinematic(true), velocity(glm::vec3(0)),
                position(glm::vec3(0)), mass(1)
    {
    }

    glm::mat4 transform;
    glm::vec3 center;

    bool hasGravity;
    bool isKinematic;
    glm::vec3 velocity;
    glm::vec3 position;
    float mass;
};
