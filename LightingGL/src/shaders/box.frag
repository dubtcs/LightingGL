
#version 330 core

in vec3 vNormal;
in vec3 fragPosition;

out vec4 color;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 eyePosition;

float ambientStrength = 0.1;
float specularStrength = 0.5;

int shine = 32;

void main(){
    // Ambient
    vec3 ambientEffect = lightColor * ambientStrength;
    ambientEffect *= objectColor;

    // Diffuse
    vec3 norm = normalize(vNormal);
    vec3 lightDirection = normalize(lightPosition - fragPosition);
    float dif = max(dot(norm, lightDirection), 0.0);
    vec3 diffuseColor = dif * lightColor;

    // Specular
    vec3 viewDirection = normalize(eyePosition - fragPosition);
    vec3 reflectDirection = reflect(-lightDirection, norm);
    float specularAmount = pow(max(dot(viewDirection, reflectDirection), 0.0), shine);
    vec3 specularColor = specularStrength * specularAmount * lightColor;

    // Output
    vec3 final = (ambientEffect + diffuseColor + specularColor) * objectColor;
    color = vec4(final, 1.0);//vec4(1.0, 0.5, 0.1, 1.0);//vec4(lightColor * objectColor, 1.f);
}
