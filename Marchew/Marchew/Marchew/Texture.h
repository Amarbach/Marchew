#pragma once
#include "include/glad/glad.h"
#include "ShaderProgram.h"
#include "stb_image.h"
#include <string>

class Texture
{
private:
	unsigned int ID;
	std::string filename;
	std::string format;
	unsigned int wrapS;
	unsigned int wrapT;
	unsigned int minFilter;
	unsigned int maxFilter;
public:
	Texture(std::string filename, std::string format);
	void Load();
	void setWrapTypeS(unsigned int type);
	void setWrapTypeT(unsigned int type);
	void setMinFilter(unsigned int filter);
	void setMaxFilter(unsigned int filter);
	void UseOn(unsigned int texUnit);
};

