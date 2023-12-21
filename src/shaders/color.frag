#version 330 core

struct Material
{
    vec3 diffuse;
};

in vec3 tFragPos;

out vec4 FragColor;

uniform Material uMaterial;

void main(void)
{
    FragColor = vec4(255.0);
}
