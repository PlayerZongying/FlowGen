#include "FlowPhysics.h"

#include <iostream>

#include "SphereCollider.h"
#include "src/FlowGL/FlowGraphics.h"
#include "src/FlowGL/VirtualObject.h"

FlowPhysics::FlowPhysics(Engine::FlowGen* aEngine)
{
    myEngine = aEngine;
}

void FlowPhysics::simulate(const float& aDeltaTime)
{
    // set the positions of colliders to  match visuals
    // std::vector<Collider*> colliders = UpdatePhysicsScene();

    colliders = UpdatePhysicsScene();
    std::vector<Collision> collisions = CheckIntersections(colliders);

    ApplyGravity(colliders, aDeltaTime);

    HandleCollision(collisions);

    ApplyVelocity(colliders, aDeltaTime);

    // // make sure the visuals of colliders are align with the colliders
    // UpdateVisuals();



    // raycast test

    Ray* ray = new Ray(glm::vec3(-8,0,0), glm::vec3(1,0,0));
    RayHit hitResult = RayHit();

    RayCast(*ray, hitResult);
}

void FlowPhysics::notSimulate()
{
    std::vector<VirtualObject*> objects = Flow::GetObjects();

    for (VirtualObject* obj : objects)
    {
        obj->SetCollider();
    }

    Ray* ray = new Ray(glm::vec3(-8,0,0), glm::vec3(1,0,0));
    RayHit hitResult = RayHit();

    RayCast(*ray, hitResult);
}

void FlowPhysics::ApplyGravity(std::vector<Collider*> colliders, const float& dt)
{
    for (Collider* c : colliders)
    {
        if (c->hasGravity && !c->isKinematic)
        {
            c->velocity += glm::vec3(0, GravityMultiplier, 0) * dt;
        }
    }
}

void FlowPhysics::ApplyVelocity(std::vector<Collider*> colliders, const float& dt)
{
    for (Collider* c : colliders)
    {
        if (!c->isKinematic)
        {
            glm::vec3 position = c->transform[3];
            position += c->velocity * dt;
            c->position = position;
            c->transform[3] = glm::vec4(position, 1.0f);
        }
    }
}

void FlowPhysics::HandleCollision(std::vector<Collision> collisions)
{
    for (Collision c : collisions)
    {
        if (!c.collider1->isKinematic)
        {
            c.collider1->velocity *= -1;
        }
        if (!c.collider2->isKinematic)
        {
            c.collider2->velocity *= -1;
        }
    }
}

std::vector<Collider*> FlowPhysics::UpdatePhysicsScene()
{
    std::vector<Collider*> colliders;

    std::vector<VirtualObject*> objects = Flow::GetObjects();

    for (VirtualObject* obj : objects)
    {
        if (!obj->collider->isKinematic)
        {
            obj->Position = obj->collider->position;
        }
        else
        {
            obj->SetCollider();
        }
        colliders.push_back(obj->collider);
    }
    return colliders;
}

std::vector<Collision> FlowPhysics::CheckIntersections(std::vector<Collider*> someColliders)
{
    std::vector<Collision> collisions;

    int count = someColliders.size();
    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            Collision c = CheckIntersect(someColliders[i], someColliders[j]);
            if (c.collider1 != nullptr && c.collider2 != nullptr)
            {
                collisions.push_back(c);
            }
        }
    }

    return collisions;
}

Collision FlowPhysics::CheckIntersect(Collider* c1, Collider* c2)
{
    // sphere sphere
    if (c1->isOf<SphereCollider>() && c2->isOf<SphereCollider>())
    {
        SphereCollider* sphere1 = dynamic_cast<SphereCollider*>(c1);
        SphereCollider* sphere2 = dynamic_cast<SphereCollider*>(c2);

        return SphereSphereIntersect(sphere1, sphere2);
    }

    // box box
    if (c1->isOf<BoxCollider>() && c2->isOf<BoxCollider>())
    {
        BoxCollider* box1 = dynamic_cast<BoxCollider*>(c1);
        BoxCollider* box2 = dynamic_cast<BoxCollider*>(c2);

        return BoxBoxIntersect(box1, box2);
    }

    // box sphere
    if ((c1->isOf<BoxCollider>() || c2->isOf<BoxCollider>()) && (c1->isOf<SphereCollider>() || c2->isOf<
        SphereCollider>()))
    {
        BoxCollider* box1 = c1->isOf<BoxCollider>() ? dynamic_cast<BoxCollider*>(c1) : dynamic_cast<BoxCollider*>(c2);
        SphereCollider* sphere2 = c1->isOf<SphereCollider>()
                                      ? dynamic_cast<SphereCollider*>(c1)
                                      : dynamic_cast<SphereCollider*>(c2);

        return BoxSphereIntersect(box1, sphere2);
    }

    Collision emptyCollision = Collision();
    return emptyCollision;
}

RayHit FlowPhysics::CheckRayIntersect(const Ray& aRay, Collider* c)
{
    if (c->isOf<SphereCollider>())
    {
        SphereCollider* sphere = dynamic_cast<SphereCollider*>(c);
        return RaySphereIntersect(aRay, sphere);
    }

    if (c->isOf<BoxCollider>())
    {
        BoxCollider* box = dynamic_cast<BoxCollider*>(c);
        return RayBoxIntersect(aRay, box);
    }

    return RayHit();
}

Collision FlowPhysics::SphereSphereIntersect(SphereCollider* sphere1, SphereCollider* sphere2)
{
    Collision collision = Collision();
    float distBetweenSphere = glm::distance(sphere1->transform[3], sphere2->transform[3]);
    float sumOfRadius = sphere1->radius + sphere2->radius;

    if (distBetweenSphere < sumOfRadius)
    {
        collision.collider1 = sphere1;
        collision.collider2 = sphere2;

        glm::vec3 dirBetweenCenters = glm::normalize(sphere2->transform[3] - sphere1->transform[3]);
        collision.point = glm::vec3(sphere1->transform[3]) + dirBetweenCenters * (sphere1->radius - (sumOfRadius -
            distBetweenSphere) * 0.5f);
    }
    return collision;
}

Collision FlowPhysics::BoxBoxIntersect(BoxCollider* box1, BoxCollider* box2)
{
    glm::mat3 rotation1 = glm::mat3(box1->transform);
    glm::mat3 rotation2 = glm::mat3(box2->transform);
    glm::vec3 translation = glm::vec3(box2->transform[3] - box1->transform[3]);
    translation = glm::transpose(rotation1) * translation;

    glm::mat3 rotation = glm::transpose(rotation1) * rotation2;
    glm::mat3 absRotation;

    for (int i = 0; i < 3; i++)
    {
        absRotation[i] = glm::abs(rotation[i]);
    }
    absRotation = absRotation + glm::mat3(0.0001f);

    // glm::mat3 absRotation = glm::abs(rotation) + glm::mat3(0.0001f);

    //SAT
    Collision collision = Collision();

    for (int i = 0; i < 3; i++)
    {
        float ra = box1->extents[i];
        float rb = glm::dot(absRotation[i], box2->extents);
        if (glm::abs(translation[i]) > ra + rb) return collision;
    }

    for (int i = 0; i < 3; i++)
    {
        float ra = glm::dot(absRotation[i], box1->extents);
        float rb = box2->extents[i];
        if (glm::abs(glm::dot(rotation[i], translation)) > ra + rb) return collision;
    }

    // has actual collision

    collision.collider1 = box1;
    collision.collider2 = box2;
    // collision.point = ;

    return collision;
}

Collision FlowPhysics::BoxSphereIntersect(BoxCollider* box1, SphereCollider* sphere2)
{
    glm::vec3 sphereCenter = glm::vec3(sphere2->transform[3]);
    glm::vec3 localSphereCenter = glm::inverse(box1->transform) * glm::vec4(sphereCenter, 1.0);
    glm::vec3 closestPoint = glm::clamp(localSphereCenter, -box1->extents, box1->extents);
    float dist = glm::length(localSphereCenter - closestPoint);

    Collision collision = Collision();

    if (dist < sphere2->radius)
    {
        collision.collider1 = box1;
        collision.collider2 = sphere2;

        glm::vec3 hitPoint = closestPoint + glm::normalize(closestPoint - localSphereCenter) * (sphere2->radius - dist)
            * 0.5f;
        glm::vec3 hitPointWorld = glm::vec3(box1->transform * glm::vec4(hitPoint, 1.0));

        collision.point = hitPointWorld;
    }
    return collision;
}

RayHit FlowPhysics::RaySphereIntersect(const Ray& aRay, SphereCollider* sphere)
{
    RayHit hitResult = RayHit();
    // sphere: (P - C) dot (P - C) = r^2
    // ray: P = O + t * D
    // combine: (t * D + O - C) dot (t * D + O - C) = r^2
    // simplify: (D dot D) * t^2 + (2 * D dot (O - C)) * t + ((O - C) dot (O - C) - r^2) = 0;

    glm::vec3 sphereCenter = glm::vec3(sphere->transform[3]);
    float sphereRadius = sphere->radius;

    float a = glm::dot(aRay.direction, aRay.direction);
    float b = 2.0f * glm::dot(aRay.direction, aRay.origin - sphereCenter);
    float c = glm::dot(aRay.origin - sphereCenter, aRay.origin - sphereCenter) - sphereRadius * sphereRadius;

    float discriminant = b * b - 4.0f * a * c;

    // if (discriminant < 0) return false;
    //
    // float tin = (-b - sqrt(discriminant)) / (2.0f * a);
    // return tin >= 0;

    if (discriminant >= 0)
    {
        float tin = (-b - sqrt(discriminant)) / (2.0f * a);
        if (tin >= 0)
        {
            hitResult.point = aRay.origin + aRay.direction * tin;
            hitResult.collider = sphere;
            hitResult.distance = tin;
        }
    }

    return hitResult;
}

RayHit FlowPhysics::RayBoxIntersect(const Ray& aRay, BoxCollider* box)
{
    glm::vec3 boxCenter = glm::vec3(box->transform[3]);
    glm::mat3 boxRotation = glm::mat3(box->transform);

    glm::vec3 localRayOrigin = aRay.origin - boxCenter;
    glm::vec3 localRayDirection = glm::transpose(boxRotation) * aRay.direction;

    Ray localRay(localRayOrigin, localRayDirection);

    return RayBoxIntersectInLocalSpace(localRay, box);
}

RayHit FlowPhysics::RayBoxIntersectInLocalSpace(const Ray& aRay, BoxCollider* box)
{
    RayHit hitResult = RayHit();

    glm::vec3 mins = -box->extents;
    glm::vec3 maxs = +box->extents;

    glm::vec3 invDir = 1.0f / glm::normalize(aRay.direction);

    float tx1 = (mins.x - aRay.origin.x) * invDir.x;
    float tx2 = (maxs.x - aRay.origin.x) * invDir.x;
    float ty1 = (mins.y - aRay.origin.y) * invDir.y;
    float ty2 = (maxs.y - aRay.origin.y) * invDir.y;
    float tz1 = (mins.z - aRay.origin.z) * invDir.z;
    float tz2 = (maxs.z - aRay.origin.z) * invDir.z;

    float tin;
    tin = std::max(std::min(tx1, tx2), std::min(ty1, ty2));
    tin = std::max(tin, std::min(tz1, tz2));

    float tout;
    tout = std::min(std::max(tx1, tx2), std::max(ty1, ty2));
    tout = std::min(tout, std::max(tz1, tz2));

    // return std::max(tin, 0.f) <= tout;

    if (std::max(tin, 0.f) <= tout)
    {
        hitResult.collider = box;
        hitResult.distance = tin;
        hitResult.point = glm::vec3(box->transform * glm::vec4((aRay.origin + aRay.direction * tin), 1.0));
    }

    return hitResult;
}


void FlowPhysics::EndStep()
{
}

bool FlowPhysics::RayCast(const Ray& aRay, RayHit& aHit)
{
    aHit = RayHit();
    for (Collider* c : colliders)
    {
        // if (CheckRayIntersect(aRay, c).collider)
        // {
        //     aHit.collider = c;
        //     aHit.point = glm::vec3(0);
        //     aHit.distance = 0;
        //     return true;
        // }
        aHit = CheckRayIntersect(aRay, c);
        if(aHit.collider)
        {
            std::cout << "Hit: ("
            <<std::to_string(aHit.point.x)<<", "
            <<std::to_string(aHit.point.y)<<", "
            <<std::to_string(aHit.point.z)<<", "
            <<")"<<std::endl;
            return true;
        }
    }

    return false;
}
