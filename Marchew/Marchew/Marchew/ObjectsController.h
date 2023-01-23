#pragma once
#include "Object.h"
#include "Carrot.h"
#include "Rabbit.h"
#include <vector>
#include"Bed.h"
#include <cmath>
#include <stdlib.h>
#include <numbers> 

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
	void killNearRabbit(glm::vec3 currentPosition);
	void eatCarrot();
	void runToCarrot(ShaderProgram& phong);
private:
	std::vector<Object*> allObjecjtsInGame;
	std::vector<Bed*> beds;
	std::vector<Carrot*> carrots;
	std::vector<Rabbit*> rabbits;
	float calculateDistance(glm::vec3 p1, glm::vec3 p2);
};

