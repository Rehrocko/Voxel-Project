#version 460 core
out vec4 FragColor;

in vec3 worldPos;

uniform vec3 viewPos;

void main()
{
    float d = (distance(viewPos, worldPos) + 1) / 300;
    FragColor = vec4(d, d, d, 1.0f);
}