#pragma once
#include <vector>

#include "Collider.h"
#include "Collision.h"
#include "src/Flow/FlowGen.h"


namespace Flow
{
    class Physics
    {
    public:
        Physics();
        void Simulate(const float& deltaTime);

        void ApplyVelocity(std::vector<Collider*> colliders, const float& dt);

        void HandleCollistions(std::vector<Collision> collisions);
        std::vector<Collider*> UpdatePhysicsScene();
        std::vector<Collision> CheckIntersections(std::vector<Collider*> colliders);

        bool CheckIntersect(Collider* col1, Collider* col2);

        void UpdateVisuals();
        void EndStep();

        

    private:
        Engine::FlowGen* myEngine;
    };
}
