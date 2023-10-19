#version 460 core
out vec4 FragColor;
void main() {
	vec3 color = vec3(0.8,0.8,0.1);
	FragColor = vec4(color,1);
}
