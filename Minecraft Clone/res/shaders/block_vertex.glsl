#version 330 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 uv;

uniform mat4 pv;
uniform mat4 model;

out vec2 uv_coords;

void main()
{
	gl_Position = pv * model * vec4(pos, 0, 1);
	uv_coords = uv;
}