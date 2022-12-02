
#version 330 core

in vec2 textureCoordinate;
in vec3 vNormal;
in vec3 fragPosition;

out vec4 color;

struct Material {
    sampler2D diffuse; // texture color
    sampler2D specular; // specular colors
    float shine;
};
uniform Material materialInfo;

struct LightDirectional{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform LightDirectional dirLight;

struct LightPoint{
    vec3 position;

    float kc;
    float kLinear;
    float kQuadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
#define AMNT_POINTLIGHT 2
uniform LightPoint pLights[2];

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 eyePosition;

float ambientStrength = 0.1;
float specularStrength = 0.5;

// Calc Functions
vec3 CalcDirectionLight(LightDirectional light, vec3 n, vec3 viewDir);
vec3 CalcPointLight(LightPoint light, vec3 n, vec3 viewDir, vec3 fragPos);

void main(){
    vec3 norm = normalize(vNormal);
    vec3 viewDirection = normalize(eyePosition - fragPosition);

    vec3 r = CalcDirectionLight(dirLight, norm, viewDirection);
    for (int i = 0; i < AMNT_POINTLIGHT; i++){
        r += CalcPointLight(pLights[i], norm, viewDirection, fragPosition);
    }

    color = vec4(r, 1.0);
}

vec3 CalcDirectionLight(LightDirectional light, vec3 n, vec3 viewDir){
    vec3 lightDirection = normalize(-light.direction);
    // Diffuse
    float diffuse = max(dot(n, lightDirection), 0);
    // Specular
    vec3 reflectDirection = reflect(-lightDirection, n);
    float specular = pow(max(dot(viewDir, reflectDirection), 0), materialInfo.shine);

    vec3 amb = light.ambient * vec3(texture(materialInfo.diffuse, textureCoordinate));
    vec3 dif = light.diffuse * diffuse * vec3(texture(materialInfo.diffuse, textureCoordinate));
    vec3 spec = light.specular * specular * vec3(texture(materialInfo.diffuse, textureCoordinate));

    return (amb + dif + spec);
}

vec3 CalcPointLight(LightPoint light, vec3 n, vec3 viewDir, vec3 fragPos){
    vec3 lightDirection = normalize(-light.position - fragPos);
    float diffuse = max(dot(n, viewDir), 0.0);
    vec3 reflectDirection = reflect(-lightDirection, n);
    float specular = pow(max(dot(viewDir, reflectDirection), 0), materialInfo.shine);

    float d = length(light.position - fragPosition);
    float attenuation = 1.0 / (light.kc + light.kLinear * d + light.kQuadratic * (d*d));

    vec3 amb = light.ambient * vec3(texture(materialInfo.diffuse, textureCoordinate));
    vec3 dif = light.diffuse * diffuse * vec3(texture(materialInfo.diffuse, textureCoordinate));
    vec3 spec = light.specular * specular * vec3(texture(materialInfo.diffuse, textureCoordinate));
    amb *= attenuation;
    dif *= attenuation;
    spec *= attenuation;

    return (amb + dif + spec);
}
