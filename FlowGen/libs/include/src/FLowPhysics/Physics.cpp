#include "Physics.h"

Flow::Physics::Physics()
{
}

void Flow::Physics::Simulate(const float& deltaTime)
{
    std::vector<Collider*> cols = UpdatePhysicsScene();

    std::vector<Collision> collisions = CheckIntersections(cols);

    HandleCollistions(collisions);

    ApplyVelocity(cols, deltaTime);

    UpdateVisuals();
}

void Flow::Physics::ApplyVelocity(std::vector<Collider*> colliders, const float& dt)
{
}

void Flow::Physics::HandleCollistions(std::vector<Collision> collisions)
{
}

std::vector<Collider*> Flow::Physics::UpdatePhysicsScene()
{
}

std::vector<Collision> Flow::Physics::CheckIntersections(std::vector<Collider*> colliders)
{
    std::vector<Collision> collisions;
    for(Collider* c1 : colliders)
    {
        for(Collider* c2 : colliders)
        {
            if(c1 != c2)
            {
                if(CheckIntersect(c1, c2))
                {
                    Collision collision;
                    
                }
                
            }
        }
    }
}

bool Flow::Physics::CheckIntersect(Collider* col1, Collider* col2)
{

}


void Flow::Physics::UpdateVisuals()
{
}

void Flow::Physics::EndStep()
{
}
