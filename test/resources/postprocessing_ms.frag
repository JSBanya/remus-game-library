#version 430 core

in vec2 TexCoords;
out vec4 FragColor;

uniform int multisample;
uniform int vp_width;
uniform int vp_height;

uniform sampler2DMS screen;

void main() {
	ivec2 vpCoords = ivec2(int(vp_width * TexCoords.x), int(vp_height * TexCoords.y));
	
	vec4 col = vec4(0);
	for(int i = 0; i < multisample; i++) {
		col += texelFetch(screen, vpCoords, i);
	}
	col /= multisample; // Simple averaging anti-aliasing
	FragColor = col;
}