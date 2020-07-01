#version 330 core

layout (location = 0) in vec4 pos;

uniform mat4 pv;

//out vec3 color;

void main()
{
	gl_Position = pv * vec4(pos.xyz, 1);
	
}