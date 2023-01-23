#pragma once
#include "ShaderProgram.h"

class Object
{
public:
	virtual void init() = 0;
	virtual void draw(ShaderProgram& phong) = 0;
	glm::vec3 position, scale;
	glm::f32 angleY;
};

