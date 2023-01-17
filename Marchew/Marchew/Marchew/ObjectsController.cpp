#include "ObjectsController.h"
#include <vector>
#include"Bed.h"
#include <cmath>

void ObjectsController::addObject(Object* object)
{
	allObjecjtsInGame.push_back(object);
}

void ObjectsController::addBed(Bed* bed)
{
	beds.push_back(bed);
}

void ObjectsController::drawObjects(ShaderProgram& phong)
{
	for (int i = 0; i < allObjecjtsInGame.size(); i++)
	{
		allObjecjtsInGame[i]->draw(phong);
	}
}

Bed* ObjectsController::findNearestBed(glm::vec3 currentPosition)
{
	float distance = 9999999;
	Bed* nearest = nullptr;
	for (int i = 0; i < beds.size(); i++)
	{
		float newDist = CalculateDistance(beds[i]->position, currentPosition);
		if (newDist < distance)
		{
			distance = newDist;
			nearest = beds[i];
		}
	}

	if (distance < 5.0f)
	{
		return nearest;
	}

	return nullptr;
}

float ObjectsController::CalculateDistance(glm::vec3 p1, glm::vec3 p2)
{
	float distance = sqrt((p1.x - p2.x) * (p1.x - p2.x)
		+ (p1.y - p2.y) * (p1.y - p2.y)
		+ (p1.z - p2.z) * (p1.z - p2.z));

	return distance;
}