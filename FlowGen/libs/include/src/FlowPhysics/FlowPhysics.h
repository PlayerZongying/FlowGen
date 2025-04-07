#pragma once
#include <vector>

#include "BoxCollider.h"
#include "Collider.h"
#include "Collision.h"
#include "Ray.h"
#include "SphereCollider.h"
#include "src/Flow/FlowGen.h"

class FlowPhysics
{
public:
    FlowPhysics(Engine::FlowGen* aEngine);
    void simulate(const float& aDeltaTime);
    void notSimulate();

    void ApplyGravity(std::vector<Collider*> colliders, const float& dt);

    void ApplyVelocity(std::vector<Collider*> colliders, const float& dt);
    void HandleCollision(std::vector<Collision> collisions);
    std::vector<Collider*> UpdatePhysicsScene();
    std::vector<Collision> CheckIntersections(std::vector<Collider*> colliders);
    void EndStep();

    std::vector<Collider*> colliders;

    bool RayCast(const Ray& aRay, RayHit& aHit);

    float GravityMultiplier = -9.8f;

private:
    Engine::FlowGen* myEngine;
    Collision CheckIntersect(Collider* vc1,Collider* c2);
    Collision SphereSphereIntersect(SphereCollider* sphere1, SphereCollider* sphere2);
    Collision BoxBoxIntersect(BoxCollider* box1, BoxCollider* box2);
    Collision BoxSphereIntersect(BoxCollider* box1, SphereCollider* sphere2);
    RayHit CheckRayIntersect(const Ray& aRay, Collider* c);
    RayHit RaySphereIntersect(const Ray& aRay, SphereCollider* sphere);
    RayHit RayBoxIntersect(const Ray& aRay, BoxCollider* box);
    RayHit RayBoxIntersectInLocalSpace(const Ray& aRay, BoxCollider* box);
};
