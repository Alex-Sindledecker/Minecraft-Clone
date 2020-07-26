#version 330 core

in vec2 uv;

uniform sampler2D tex;

out vec4 color;

void main()
{
	float val = texture(tex, (uv + 1) / 2).r;
	color = vec4(texture(tex, (uv + 1) / 2).rgb, 1);
}