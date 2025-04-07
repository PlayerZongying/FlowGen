#pragma once
#include "Collider.h"

class SphereCollider : public Collider
{
public:
    SphereCollider(): radius(1)
    {
    }
    
    float radius;
};
