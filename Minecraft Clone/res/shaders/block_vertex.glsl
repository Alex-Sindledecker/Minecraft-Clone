#version 330 core

layout (location = 0) in uint vertex;

uniform mat4 pv;
uniform vec3 chunk_pos;

out vec2 uv;
out uint normal;

vec2 uvs[4] = vec2[4](
	vec2(1.0/16.0, 0),
	vec2(0, 0),
	vec2(0, 1.0/16.0),
	vec2(1.0/16.0, 1.0/16.0)
);

void main()
{
	float x = (vertex & 0x3F000u) >> 12u;
	float y = (vertex & 0xFC0u) >> 6u;
	float z = vertex & 0x03Fu;
	gl_Position = pv * vec4(x + chunk_pos.x, y + chunk_pos.y, z + chunk_pos.z, 1);
	
	normal = (vertex & 0x1C0000u) >> 18u;
	uv = uvs[(vertex & 0x600000u) >> 21u];
	float uv_index = (vertex & 0x7f800000u) >> 23u;
	uv.x += uv_index * (1.0 / 16.0);
}