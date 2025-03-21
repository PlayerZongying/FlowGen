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
uniform sampler2D specularMap;
uniform sampler2D shadowMap;

in vec3 FragPos;
in vec2 uv;
in vec3 Normal;
in vec3 ViewPos;
in vec4 FragPosLightSpace;

out vec4 FragColor;

float ShadowCalculation(vec3 lightPos, vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // calculate bias (based on depth map resolution and slope)
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    // check whether current frag pos is in shadow
    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    
    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadow = 0.0;
        
    return shadow;
}

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
            vec3 specular = light.specular * (spec * texture(specularMap, uv).r);

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
            vec3 specular = light.specular * (spec * texture(specularMap, uv).r);

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
            
            float spotDotCutoff = dot(-lightDir, normalize(light.direction));
            if(spotDotCutoff >= cos(radians(light.angle)))
            {
                // diffuse
                float diff = max(dot(norm, lightDir), 0.0);
                diffuse = light.diffuse * (diff * material.diffuse);

                // specular
                vec3 halfwayDir = normalize(lightDir + viewDir);
                float spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
                specular = light.specular * (spec * texture(specularMap, uv).r);
            }
            
            // ambient
            vec3 ambient = light.ambient * material.ambient;
            
            // shadow
            float shadow = 0.0f;
            if(i < 0.5f)
            {
                shadow = ShadowCalculation(light.position, FragPosLightSpace);
            
            }

            FragColor += vec4(ambient + (1.0 - shadow) * (diffuse + specular), 1.0) * texture(diffuseTexture, uv);
        }
    
    
    }

    //FragColor = vec4(texture(diffuseTexture, uv).rgb, 1.0);
    //FragColor = vec4(texture(specularMap, uv).rgb, 1.0);
    //FragColor = vec4(1); 
    //FragColor = testColor;
    
    //FragColor = vec4(lights[0].ambient,1);
    //FragColor.xy = uv;
    //FragColor = vec4((norm + vec3(1.0f)) * 0.5f, 1.0f);
    
}