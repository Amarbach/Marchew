#pragma once
#include "Object.h"
#include "Carrot.h"
#include "Rabbit.h"
#include <vector>

class Bed;

class ObjectsController
{
public:
	ObjectsController();
	void addObject(Object* object);
	void addRabbit(Rabbit* rabbit);
	void removeObject(Object* object);
	void addBed(Bed* bed);
	void addCarrot(Carrot* carrot);
	void removeCarrot(Carrot* carrot);
	void drawObjects(ShaderProgram& phong);
	void drawRabbits(ShaderProgram& phong);
	void spawnRabbits(int quant);
	Bed* findNearestBed(glm::vec3 currentPosition);
	void carrotsGrowing(float elapsed);
	void KillNearRabbit(glm::vec3 currentPosition);
	void EatCarrot();
	void runToCarrot(float elapsed);
private:
	std::vector<Object*> allObjecjtsInGame;
	std::vector<Bed*> beds;
	std::vector<Carrot*> carrots;
	std::vector<Rabbit*> rabbits;
	float CalculateDistance(glm::vec3 p1, glm::vec3 p2);
};

