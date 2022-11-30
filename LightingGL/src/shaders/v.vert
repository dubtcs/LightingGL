
#version 330 core

layout (location = 0) in vec3 inPos;

uniform mat4 toWorldSpace;
uniform mat4 toViewSpace;
uniform mat4 toClipSpace;

void main(){
    gl_Position = toClipSpace * toViewSpace * toWorldSpace * vec4(inPos, 1.0);
}
