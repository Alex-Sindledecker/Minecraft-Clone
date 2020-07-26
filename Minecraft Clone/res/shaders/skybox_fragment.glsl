#version 330 core

in vec3 uv;

uniform samplerCube skybox;

out vec4 color;

void main()
{
	color = vec4(texture(skybox, uv).rgb, 1);
}