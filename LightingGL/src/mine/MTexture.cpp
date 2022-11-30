
#define STB_IMAGE_IMPLEMENTATION

#include "MTexture.h"
#include "../extern/stb_image.h"
#include <iostream>

MTexture::MTexture(const std::string& path, GLenum slot) {
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // S,T,R coordinates
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* imageData = stbi_load(path.c_str(), &texWidth, &texHeight, &colorChannels, 0);
	bindSlot = slot;
	if (imageData) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texWidth, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "bruh";
	}
	stbi_image_free(imageData);
}

void MTexture::Bind() {
	glActiveTexture(bindSlot);
	glBindTexture(GL_TEXTURE_2D, id);
	glActiveTexture(0);
}
void MTexture::Bind(GLenum slot) {
	glActiveTexture(slot);
	glBindTexture(GL_TEXTURE_2D, id);
	glActiveTexture(0);
}
