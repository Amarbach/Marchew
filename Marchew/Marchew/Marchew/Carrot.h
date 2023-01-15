#pragma once
#include "Object.h"
#include "include/glm/glm.hpp"
#include "Texture.h"
#include "Model.h"

class Carrot : public Object
{
public:
	Carrot();
	void init();
	void draw(ShaderProgram& phong);
private:
	Model* model;
	Texture* texture;
};

