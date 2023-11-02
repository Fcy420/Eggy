#version 460 core
out vec4 FragColor;
vec4 color = vec4(1);
void main() {
	vec3 pixelColor = color.xyz;
	FragColor = vec4(pixelColor,1);
}
