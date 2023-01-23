#pragma once
#include "Object.h"
#include "Rabbit.h"
#include "Carrot.h"
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
	void removeObject(Object* object);
	void addBed(Bed* bed);
	void addCarrot(Carrot* carrot);
	void removeCarrot(Carrot* carrot);
	Bed* findNearestBed(glm::vec3 currentPosition);
	void drawObjects(ShaderProgram& phong);
	void handleRabbits(glm::vec3 currentPosition, ShaderProgram& phong);
	void drawRabbits(ShaderProgram& phong);
	void spawnRabbits(int quant);
	void reSpawnRabbits();
	void carrotsGrowing(float elapsed);
	void killNearRabbit(glm::vec3 currentPosition);
	void eatCarrot();
	void rabbitRun();
private:
	std::vector<Object*> allObjecjtsInGame;
	std::vector<Bed*> beds;
	std::vector<Carrot*> carrots;
	std::vector<Rabbit*> rabbits;
	
	float calculateDistance(glm::vec3 p1, glm::vec3 p2);
};

