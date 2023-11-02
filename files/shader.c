#include "renderer.h"

void init_shader(Shader* shader, const char* vert, const char* frag) {
	FILE* file;
	long size;
	char* buffer;
	file = fopen(vert, "rb");
	if(!file)perror(vert),exit(1);
	fseek(file, 0L, SEEK_END);
	size = ftell(file);
	rewind(file);
	buffer = calloc(1, size+1);
	if(!buffer) fclose(file),fputs("memory alloc failed",stderr),exit(1);
	if(1!=fread(buffer, size, 1, file)) {
		fclose(file),free(buffer),fputs("Read failed quitting",stderr),exit(1);
	}
	fclose(file);	
	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &buffer, NULL);
	glCompileShader(vertex_shader);
	free(buffer);
	file = fopen(frag, "rb");
	if(!file)perror(frag),exit(1);
	fseek(file, 0L, SEEK_END);
	size = ftell(file);
	rewind(file);
	buffer = calloc(1, size+1);
	if(!buffer)fclose(file),fputs("memory alloc failed",stderr),exit(1);
	if(1!=fread(buffer,size,1,file)) {
		fclose(file),free(buffer),fputs("Read failed quitting",stderr),exit(1);
	}
	fclose(file);
	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &buffer, NULL);
	glCompileShader(fragment_shader);
	shader->program = glCreateProgram();
	glAttachShader(shader->program, vertex_shader);
	glAttachShader(shader->program, fragment_shader);
	glLinkProgram(shader->program);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	free(buffer);
}
void use_shader(Shader* shader) {
	if(shader == NULL) {
		glUseProgram(0);
		return;
	}
	glUseProgram(shader->program);
}

void set_shader_int(Shader* shader, const char* uniform, int val) {
	glUniform1i(glGetUniformLocation(shader->program, uniform), val);
}

void set_shader_float(Shader* shader, const char* uniform, float val) {
	glUniform1f(glGetUniformLocation(shader->program, uniform), val);
}

void set_shader_vec4(Shader* shader, const char* uniform, vec4 val) {
	glUniform4fv(glGetUniformLocation(shader->program, uniform), 1, (float*)val);
}

void set_shader_mat4(Shader* shader, const char *uniform, mat4 val) {
	glUniformMatrix4fv(glGetUniformLocation(shader->program, uniform), 1, GL_FALSE, (float*)val);
}

void destroy_shader(Shader *shader) {
	glDeleteProgram(shader->program);
}
