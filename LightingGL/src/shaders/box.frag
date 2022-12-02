
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
    vec3 direction;
    float cutoff;
    float innerCutoff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float kc;
    float kLinear;
    float kQuadratic;
};
uniform Light lightInfo;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 eyePosition;

float ambientStrength = 0.1;
float specularStrength = 0.5;

void main(){
    vec3 lightDirection = normalize(lightInfo.position - fragPosition);
    float angle = dot(lightDirection, normalize(-lightInfo.direction));
    vec3 stage1 = vec3(0, 0, 0);
    if (angle > lightInfo.cutoff){
        float innerAngle = lightInfo.innerCutoff - lightInfo.cutoff;
        float intensity = clamp((angle - lightInfo.cutoff) / innerAngle, 0.0, 1.0);
        // Diffuse
        vec3 norm = normalize(vNormal);
        float dif = max(dot(norm, lightDirection), 0.0);
        vec3 diffuseColor = lightInfo.diffuse * dif * vec3(texture(materialInfo.diffuse, textureCoordinate));
        // Specular
        vec3 viewDirection = normalize(eyePosition - fragPosition);
        vec3 reflectDirection = reflect(-lightDirection, norm);
        float specularAmount = pow(max(dot(viewDirection, reflectDirection), 0.0), materialInfo.shine);
        vec3 specularColor = lightInfo.specular * specularAmount * vec3(texture(materialInfo.specular, textureCoordinate));

        stage1 = (specularAmount + diffuseColor) * intensity;
    }
    // Ambient
    vec3 ambientEffect = lightInfo.ambient * vec3(texture(materialInfo.diffuse, textureCoordinate));
    stage1 += ambientEffect;

    // Attenuation
    float d = length(lightInfo.position - fragPosition);
    float attenuation = 1.0 / (lightInfo.kc + lightInfo.kLinear * d + lightInfo.kQuadratic * (d * d));

    stage1 *= attenuation;

    // Output
    //vec3 final = (ambientEffect + diffuseColor + specularColor);
    color = vec4(stage1, 1.0);//vec4(1.0, 0.5, 0.1, 1.0);//vec4(lightColor * objectColor, 1.f);
}
