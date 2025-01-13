#version 330 core

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Light light;
uniform Material material;
uniform vec4 testColor;

uniform vec3 viewPos;
uniform sampler2D diffuseTexture;

in vec3 FragPos;
in vec3 Normal;
in vec3 ViewPos;
in vec2 texcoord;

out vec4 FragColor;

void main() {

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    vec3 viewDir = normalize(ViewPos - FragPos);

    // diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * vec3(texture(diffuseTexture, texcoord)));

    // specular
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);

    // ambient
    vec3 ambient = light.ambient * material.ambient;


    //FragColor = vec4(1); 
    //FragColor = testColor;
    FragColor = vec4(ambient + diffuse + specular, 1.0);
    
    FragColor.xy = texcoord.xy;
    
    //FragColor = texture(diffuseTexture, texcoord);
    
    //FragColor = vec4((norm + vec3(1.0f)) * 0.5f, 1.0f);
}