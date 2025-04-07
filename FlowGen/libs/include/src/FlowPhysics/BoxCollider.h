#pragma once
#include "Collider.h"

class BoxCollider:public Collider
{
public:
    BoxCollider(): extents(glm::vec3(1))
    {
    }

    BoxCollider(const glm::vec3& aCenter,const glm::vec3& someExtents)
    {
        velocity = glm::vec3(0.0);
        hasGravity = false;
        center = aCenter;
        extents = someExtents;
    }
    glm::vec3 extents;
};
