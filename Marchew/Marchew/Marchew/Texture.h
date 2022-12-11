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
	unsigned int wrapS;
	unsigned int wrapT;
	unsigned int minFilter;
	unsigned int maxFilter;
public:
	Texture(std::string filename);
	void Load();
	void setWrapTypeS(unsigned int type);
	void setWrapTypeT(unsigned int type);
	void setMinFilter(unsigned int filter);
	void setMaxFilter(unsigned int filter);
	void UseOn(unsigned int texUnit);
	std::string getFilename();
};

