#pragma once
#include <glm/glm.hpp>

enum LightType
{
    none,
    directional,
    point,
    spot
};


class Light
{
public:
    LightType lightType;

    glm::vec3 position; // for point & spot
    glm::vec3 direction; // for directional & spot

    float intensity;
    float length; // for point & spot
    float angle; // for spot

    // light color
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    Light();
    // Light(
    //     LightType _lightType = LightType::none,
    //     glm::vec3 _position = {0, 0, 0},
    //     glm::vec3 _direction = {0, 0, 0},
    //     float _intensity = 1,
    //     float _length = 10,
    //     float _angle = 45,
    //     glm::vec3 _ambient = {0, 0, 0},
    //     glm::vec3 _diffuse = {1, 1, 1},
    //     glm::vec3 _specular = {1, 1, 1}
    // );
};
