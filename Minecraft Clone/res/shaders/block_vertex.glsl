#version 330 core

layout (location = 0) in uint vertex;

uniform mat4 pv;

//out vec3 color;

// 0b00000000000000000000 0000 0000 0000
//                          x    y   z


void main()
{
	float x = (vertex & 0x7C00u) >> 10u;
	float y = (vertex & 0x3E0u) >> 5u;
	float z = vertex & 0x0Fu;

	gl_Position = pv * vec4(x, y, z, 1);
	
}