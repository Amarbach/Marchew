#pragma once
#include "Object.h"
#include "include/glm/glm.hpp"
#include "Texture.h"
#include "Model.h"
#include "Carrot.h"
#include <numbers> 



class Rabbit : public Object
{
public:
	Rabbit();
	~Rabbit();
	Rabbit(glm::vec3 _position);
	void init();
	void draw(ShaderProgram& phong);
	void runToCarrot();
	void runForward();
	Carrot* carrot;
	void rotate();

private:
	float carrotDistance();
	float carrotAngle();
	Model* model;
	Texture* texture;
	float speed;
};

