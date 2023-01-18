#pragma once
#include "Object.h"
#include "include/glm/glm.hpp"
#include "Texture.h"
#include "Model.h"
#include <vector>

class ObjectsController;
class Carrot;

class Bed : public Object
{
public:
	Bed();
	Bed(glm::vec3 _position, glm::vec3 _scale);
	void init();
	void draw(ShaderProgram& phong);
	void seedCarrot(ObjectsController& objectsController);
	void takeCarrot(ObjectsController& objectsController);
private:
	std::vector<glm::vec3> carrotPositions;
	std::vector<Carrot*> carrots;
	Model* model;
	Texture* texture;
};

