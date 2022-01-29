#version 330 core

layout (location = 0) in uint vertex;

uniform mat4 mvp;
uniform vec3 chunkPos;

struct VertexInfo
{
	vec3 pos;
	uint atlasIndex;
	uint imageCorner;
};

VertexInfo decompressVertex(uint vertex)
{
	VertexInfo info;

	//        c    i       z     y       x
	//000000 00 00000000 0000 00000000 0000
	//00000000000000000000000000000000
	info.pos.x = vertex & 0xFu;
    info.pos.y = (vertex & 0xFF0u) >> 4u;
    info.pos.z = (vertex & 0xF000u) >> 12u;
    info.atlasIndex = (vertex & 0xFF0000u) >> 16u;
    info.imageCorner = (vertex & 0x3000000u) >> 24u;

	return info;
}

void main()
{
   VertexInfo vertexInfo = decompressVertex(vertex);
   gl_Position = mvp * vec4(vertexInfo.pos + chunkPos, 1.0);
}