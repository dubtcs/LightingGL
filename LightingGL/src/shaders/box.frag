
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

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light lightInfo;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 eyePosition;

float ambientStrength = 0.1;
float specularStrength = 0.5;

void main(){
    // Ambient
    vec3 ambientEffect = lightInfo.ambient * vec3(texture(materialInfo.diffuse, textureCoordinate));
    //ambientEffect *= objectColor;

    // Diffuse
    vec3 norm = normalize(vNormal);
    vec3 lightDirection = normalize(lightInfo.position - fragPosition);
    float dif = max(dot(norm, lightDirection), 0.0);
    vec3 diffuseColor = lightInfo.diffuse * dif * vec3(texture(materialInfo.diffuse, textureCoordinate));

    // Specular
    vec3 viewDirection = normalize(eyePosition - fragPosition);
    vec3 reflectDirection = reflect(-lightDirection, norm);
    float specularAmount = pow(max(dot(viewDirection, reflectDirection), 0.0), materialInfo.shine);
    vec3 specularColor = lightInfo.specular * specularAmount * vec3(texture(materialInfo.specular, textureCoordinate));

    // Output
    vec3 final = (ambientEffect + diffuseColor + specularColor);
    color = vec4(final, 1.0);//vec4(1.0, 0.5, 0.1, 1.0);//vec4(lightColor * objectColor, 1.f);
}
