
#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoord;

out vec2 textureCoordinate;
out vec3 vNormal;
out vec3 fragPosition;

uniform mat4 toWorldSpace;
uniform mat4 toViewSpace;
uniform mat4 toClipSpace;

void main(){
    gl_Position = toClipSpace * toViewSpace * toWorldSpace * vec4(inPos, 1.0);
    //vNormal = inNormal;
    vNormal = mat3(transpose(inverse(toWorldSpace))) * inNormal;  
    fragPosition = vec3(toWorldSpace * vec4(inPos, 1.0));
    textureCoordinate = inTexCoord;
}
