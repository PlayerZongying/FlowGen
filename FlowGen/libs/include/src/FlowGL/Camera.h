#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace Flow
{

    class Camera
    {
    private:

        glm::vec3 myPosition;
        glm::vec3 myDirection;

        glm::vec3 myUp;
        glm::vec3 myRight;

        float fieldOfView = 45;
        glm::vec2 cameraSize;

    public:
        float get_field_of_view() const;
        void set_field_of_view(float field_of_view);

        glm::mat4 myProjection;
        glm::mat4 myView;

        Camera(const float& aWidth, const float& aHeight);

        void CameraUpdate();
        void CameraUpdate(GLFWwindow* window);

        void SetPosition(const glm::vec3& aPosition);
        void SetRotation(const glm::vec3& aRotation);

        void Move(const glm::vec3& aMove);
        glm::vec3 GetDirection();
        void SetDirection(const glm::vec3& aDirection);

        void SetProjection();

        glm::vec3 GetPosition();
    };
    
}

