#pragma once
#include "Object.h"
#include "include/glm/glm.hpp"
#include "Texture.h"
#include "Model.h"
#include <vector>

class Bed : public Object
{
public:
	Bed();
	void init();
	void draw(ShaderProgram& phong);
private:
	std::vector<glm::vec3> carrotPositions;
	Model* model;
	Texture* texture;
};

