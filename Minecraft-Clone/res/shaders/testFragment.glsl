#version 330 core

in vec2 uv;

uniform sampler2D tex;

out vec4 FragColor;

void main()
{
   FragColor = texture(tex, uv);
}