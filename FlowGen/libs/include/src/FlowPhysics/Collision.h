#pragma once
#include "Collider.h"

struct Collision
{
    Collision()
    {
        collider1 = nullptr;
        collider2 = nullptr;
        point = glm::vec3(0);
    }
    Collider* collider1;
    Collider* collider2;
    
    glm::vec3 point;
};
