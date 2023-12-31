#version 460 core
out vec4 FragColor;

in vec2 uv;

uniform sampler2D tex0;

void main() {
	vec3 rgb = texture(tex0, uv).rgb;
	FragColor = vec4(rgb, 1.0);
}
