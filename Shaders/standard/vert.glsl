#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 normal;

uniform mat4 Projection;
uniform mat4 Transform;

void main() {
	normal = aNormal;
	gl_Position = Projection * Transform * vec4(aPos, 1.0);
}
