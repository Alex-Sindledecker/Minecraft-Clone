#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 mvp;

out vec2 uv;

void main()
{
   gl_Position = mvp * vec4(aPos * 5, 1.0);

   uv = vec2(aPos.x + 0.5, aPos.y + 0.5);
}