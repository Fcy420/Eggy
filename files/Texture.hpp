#pragma once

#include "../libraries/glm/glm/glm.hpp"
#include "../libraries/glad/glad.h"
#include "../libraries/glfw/include/GLFW/glfw3.h"

namespace Texture {

	enum Filter {
		POINT,
		LINEAR
	};
	
	struct Texture {
		GLuint ID, slot;
	}; 
	
	inline void GenerateTexture2D(Texture* tex, int slot = 0, Filter filter = POINT) {
		glActiveTexture(GL_TEXTURE0 + slot);
		glGenTextures(1, &tex->ID);	
		glBindTexture(GL_TEXTURE_2D, tex->ID);
		switch(filter) {
			case POINT:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
				break;

			case LINEAR:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
				break;
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glBindTexture(GL_TEXTURE_2D, 0);	
	}
	
	inline void Load(Texture* tex, const char* path) {
		

	}
	
	inline void DestroyTexture(Texture* tex) {
		glDeleteTextures(1, &tex->ID);
	}


}
