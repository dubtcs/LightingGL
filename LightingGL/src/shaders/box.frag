
#version 330 core

out vec4 color;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main(){
    color = vec4(1.0, 0.5, 0.1, 1.0);//vec4(lightColor * objectColor, 1.f);
}
