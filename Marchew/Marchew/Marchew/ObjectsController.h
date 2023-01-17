#pragma once
#include "Object.h"
#include <vector>

class Bed;

class ObjectsController
{
public:
	void addObject(Object* object);
	void addBed(Bed* bed);
	void drawObjects(ShaderProgram& phong);
	Bed* findNearestBed(glm::vec3 currentPosition);
private:
	std::vector<Object*> allObjecjtsInGame;
	std::vector<Bed*> beds;
	float CalculateDistance(glm::vec3 p1, glm::vec3 p2);
};

