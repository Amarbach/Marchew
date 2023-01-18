#pragma once
#include "Object.h"
#include "Carrot.h"
#include <vector>

class Bed;

class ObjectsController
{
public:
	void addObject(Object* object);
	void removeObject(Object* object);
	void addBed(Bed* bed);
	void addCarrot(Carrot* carrot);
	void removeCarrot(Carrot* carrot);
	void drawObjects(ShaderProgram& phong);
	Bed* findNearestBed(glm::vec3 currentPosition);
	void carrotsGrowing(float elapsed);
private:
	std::vector<Object*> allObjecjtsInGame;
	std::vector<Bed*> beds;
	std::vector<Carrot*> carrots;
	float CalculateDistance(glm::vec3 p1, glm::vec3 p2);
};

