#pragma once
#include <glm/glm.hpp>

class Collider
{
public:
    virtual ~Collider(){}

    template<typename T>
    bool isOf(){return (dynamic_cast<T*>(this) != nullptr);}

    glm::mat4 transform;
    glm::vec4 center;

    bool hasGravity;
    glm::vec3 velocity;
    float mass;
};
