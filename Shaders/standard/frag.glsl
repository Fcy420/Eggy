#version 460 core
out vec4 FragColor;

in vec3 normal;

uniform vec3 color;
uniform mat3 NormalTransform;
vec3 lightDirection = vec3(1);
float ambientLight = 0.2;

vec2 CalcLighting() {
	vec3 rotatedNormals = normalize(NormalTransform * normal);
	vec3 lightDir = normalize(lightDirection);
	float diffuse = max(dot(rotatedNormals, lightDir), ambientLight);	
	return vec2(diffuse, 0.0);
}


void main() {
	vec3 pixel = color;
	vec2 light = CalcLighting();
	pixel *= light.x;
	FragColor = vec4(pixel,1);
}
