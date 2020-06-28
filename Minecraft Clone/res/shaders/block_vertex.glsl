#version 330 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 uv;

out vec2 uv_coords;

void main()
{
	gl_Position = vec4(pos, 0, 1);
	uv_coords = uv;
}