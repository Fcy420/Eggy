#version 460 core
out vec4 FragColor;

in vec2 uv;

uniform sampler2D screen;

void main() {
	vec3 tex = texture(screen, uv).rgb;
	FragColor = vec4(tex, 1.0);
}
