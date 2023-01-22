#pragma once
#include "Object.h"
#include "include/glm/glm.hpp"
#include "Texture.h"
#include "Model.h"
#include "Carrot.h"

class Rabbit : public Object
{
public:
	Rabbit();
	~Rabbit();
	Rabbit(glm::vec3 _position, float angleY);
	void init();
	void draw(ShaderProgram& phong);
	void runToCarrot();
	void runForward();
	Carrot* carrot;
private:
	float CalculateCarrotDistance();
	Model* model;
	Texture* texture;
	float speed;
};

