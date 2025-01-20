#version 330 core
#define MAX_LIGHTS	9 

struct Light {
    int lightType;
    
    vec3 position;
    vec3 direction;
    
    float intensity;
    float length;
    float angle;
    
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

//uniform Light light;
uniform Light lights[MAX_LIGHTS];
uniform Material material;

uniform vec3 viewPos;
uniform sampler2D diffuseTexture;

in vec3 FragPos;
in vec2 uv;
in vec3 Normal;
in vec3 ViewPos;

out vec4 FragColor;

void main() {

    FragColor = vec4(0,0,0,1);
    
    for(int i = 0; i < MAX_LIGHTS; i++)
    {
        Light light = lights[i];
        
        // directional light
        if(light.lightType == 1)
        {
        vec3 norm = normalize(Normal);
            vec3 lightDir = light.direction;
            vec3 viewDir = normalize(ViewPos - FragPos);

            // diffuse
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 diffuse = light.diffuse * (diff * material.diffuse);

            // specular
            vec3 halfwayDir = normalize(lightDir + viewDir);
            float spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
            vec3 specular = light.specular * (spec * material.specular);

            // ambient
            vec3 ambient = light.ambient * material.ambient;

            FragColor += vec4(ambient + diffuse + specular, 1.0) * texture(diffuseTexture, uv);
        
        
        }
        
        // point light
        if(light.lightType == 2)
        {
            vec3 norm = normalize(Normal);
            vec3 lightDir = normalize(light.position - FragPos);
            vec3 viewDir = normalize(ViewPos - FragPos);

            // diffuse
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 diffuse = light.diffuse * (diff * material.diffuse);

            // specular
            vec3 halfwayDir = normalize(lightDir + viewDir);
            float spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
            vec3 specular = light.specular * (spec * material.specular);

            // ambient
            vec3 ambient = light.ambient * material.ambient;

            FragColor += vec4(ambient + diffuse + specular, 1.0) * texture(diffuseTexture, uv);
        }
        
        // spot light
        if(light.lightType == 3)
        {
            vec3 norm = normalize(Normal);
            vec3 lightDir = normalize(light.position - FragPos);
            vec3 viewDir = normalize(ViewPos - FragPos);
            
            vec3 diffuse = vec3(0);
            vec3 specular = vec3(0);;
            
            float spotDotCutoff = dot(-lightDir, light.direction);
            if(spotDotCutoff >= cos(radians(light.angle)))
            {
                // diffuse
                float diff = max(dot(norm, lightDir), 0.0);
                diffuse = light.diffuse * (diff * material.diffuse);

                // specular
                vec3 halfwayDir = normalize(lightDir + viewDir);
                float spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
                specular = light.specular * (spec * material.specular);
            }
            
            // ambient
            vec3 ambient = light.ambient * material.ambient;

            FragColor += vec4(ambient + diffuse + specular, 1.0) * texture(diffuseTexture, uv);
        }
    
    
    }


    //FragColor = vec4(1); 
    //FragColor = testColor;
    
    //FragColor = vec4(lights[0].ambient,1);
    //FragColor.xy = uv;
    //FragColor = vec4((norm + vec3(1.0f)) * 0.5f, 1.0f);
    
}