#version 330 core

layout(location = 0) in vec3 aPosition;
// layout(location = 1) in vec3 aColor;

uniform vec3 spherePos;

out vec3 tFragPos;

void main(void){
    tFragPos = aPosition + spherePos;
}