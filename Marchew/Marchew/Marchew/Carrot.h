#pragma once
#include "Object.h"
#include "include/glm/glm.hpp"
#include "Texture.h"
#include "Model.h"
#include "Bed.h"

class Carrot : public Object
{
public:
	Carrot();
	Carrot(glm::vec3 _position, glm::vec3 _scale);
	void init();
	void draw(ShaderProgram& phong);
	Bed* connectedToBed;
private:
	Model* model;
	Texture* texture;
};

