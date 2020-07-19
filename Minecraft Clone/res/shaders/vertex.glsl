#version 330 core

layout (location = 0) in vec3 vertex;

uniform mat4 pv;

out vec2 uv;

void main()
{
	gl_Position = pv * vec4(vertex, 1);
	
	uv = vertex.xy;
}