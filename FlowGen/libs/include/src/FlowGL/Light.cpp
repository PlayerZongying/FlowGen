#include "Light.h"

Light::Light()
{
    lightType = LightType::none;
    position = {0, 0, 0};
    direction = {0, 0, 0};
    intensity = 1;
    length = 10;
    angle = 45;
    ambient = {0, 0, 0};
    diffuse = {1, 1, 1};
    specular = {1, 1, 1};
}

// Light::Light(
//     LightType _lightType,
//     glm::vec3 _position,
//     glm::vec3 _direction,
//     float _intensity,
//     float _length,
//     float _angle,
//     glm::vec3 _ambient,
//     glm::vec3 _diffuse,
//     glm::vec3 _specular)
// {
//     lightType = _lightType;
//     position = _position;
//     direction = _direction;
//
//     intensity = _intensity;
//     length = _length;
//     angle = _angle;
//     ambient = _ambient;
//     diffuse = _diffuse;
//     specular = _specular;
//     
// }
