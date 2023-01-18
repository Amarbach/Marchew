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
	~Carrot();
	Carrot(glm::vec3 _position, glm::vec3 _scale);
	void init();
	void draw(ShaderProgram& phong);
	void grow(float elapsed);
	Bed* connectedToBed;
	bool isGrowing;
private:
	Model* model;
	Texture* texture;
	float growingTime = 80000.0f;
	float naive_lerp(float a, float b, float t);
};

