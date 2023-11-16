#include "renderer.h"
#include "window.h"

void init_display(Display *display, int width, int height, const char* shader) {
	glGenFramebuffers(1, &display->fbo);
	glGenRenderbuffers(1, &display->rbo);
	glGenTextures(1, &display->tex);
	glBindFramebuffer(GL_FRAMEBUFFER, display->fbo);
	glBindTexture(GL_TEXTURE_2D, display->tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, display->tex, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, display->rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	display->width = width;
	display->height = height;

	init_mesh(&display->mesh);
	float vertices[] = {
		-1,-1,0, 0,0,0, 0,0,
		1,-1,0, 0,0,0, 1,0,
		-1,1,0, 0,0,0, 0,1,
		1,1,0, 0,0,0, 1,1,
	};
	unsigned int triangles[] = {
		0,1,2,3,2,1
	};
	create_mesh(&display->mesh, vertices, 12, triangles, 6);
	init_material(&display->material, shader);
}
void bind_display(Display* display) {
	glBindFramebuffer(GL_FRAMEBUFFER, display->fbo);
}
void unbind_displays() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void view_display(Display* display) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, display->tex);
	bind_material(&display->material);
	draw_mesh(&display->mesh);
}

void destroy_display(Display *display) {
	glDeleteFramebuffers(1, &display->fbo);
	glDeleteRenderbuffers(1, &display->rbo);
	glDeleteTextures(1, &display->tex);
	destroy_mesh(&display->mesh);
}
