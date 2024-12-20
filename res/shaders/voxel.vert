#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 worldPos;
  
uniform mat4 viewPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    worldPos = (model * vec4(aPos.x, aPos.y, aPos.z, 1.0)).xyz;

    gl_Position = projection * view * vec4(worldPos, 1.0);

    TexCoord = aTexCoord;
} 