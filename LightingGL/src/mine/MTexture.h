#pragma once

#include <glad/glad.h>
#include <string>

class MTexture {
public:
	MTexture(const std::string& path, GLenum s);
public:
	void Bind();
	void Bind(GLenum);
private:
	GLenum bindSlot;
	int texWidth, texHeight, colorChannels;
	unsigned int id;
};
