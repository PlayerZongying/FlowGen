#pragma once
#include <glm/fwd.hpp>
#include <glm/glm.hpp>

#include "Collider.h"

class Ray
{
public:

    Ray(const glm::vec3& anOrigin, const glm::vec3& aDirection)
    {
        origin = aDirection;
        direction = aDirection;
    }
    
    glm::vec3 origin;
    glm::vec3 direction;
};

struct RayHit
{
    RayHit()
    {
        point = glm::vec3(0);
        collider = nullptr;
        distance = 0;
    }
    RayHit(glm::vec3 aPoint, Collider* aCollider, float aDistance)
    {
        point = aPoint;
        collider = aCollider;
        distance = aDistance;
    }

    glm::vec3 point;
    Collider* collider;
    float distance;
};
