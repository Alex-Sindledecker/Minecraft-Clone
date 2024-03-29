#version 330 core

layout (location = 0) in uint vertex;

uniform mat4 mvp;
uniform vec2 chunkPos;

out vec3 normal;

struct VertexInfo
{
	vec3 pos;
	uint atlasIndex;
	uint normal;
};

VertexInfo decompressVertex(uint vertex)
{
	VertexInfo info;

	//        c    i       z     y       x
	//000000 000 00000000 0000 00000000 0000
	//00000000000000000000000000000000
	info.pos.x = vertex & 0xFu;
    info.pos.y = (vertex & 0xFF0u) >> 4u;
    info.pos.z = (vertex & 0xF000u) >> 12u;
    info.atlasIndex = (vertex & 0xFF0000u) >> 16u;
    info.normal = (vertex & (0xFFu << 24u)) >> 24u;

	return info;
}

void main()
{
	vec3 normalList[] = vec3[](vec3(1, 0, 0), vec3(-1, 0, 0), vec3(0, 1, 0), vec3(0, -1, 0), vec3(0, 0, 1), vec3(0, 0, -1));

	VertexInfo vertexInfo = decompressVertex(vertex);
	gl_Position = mvp * vec4(vertexInfo.pos + vec3(chunkPos.x, 0, chunkPos.y), 1.0);

	normal = normalList[vertexInfo.normal];
}