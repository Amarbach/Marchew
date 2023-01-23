#include "ObjectsController.h"



void ObjectsController::addObject(Object* object)
{
	allObjecjtsInGame.push_back(object);
}

void ObjectsController::removeObject(Object* object)
{
	for (int i = 0; i < allObjecjtsInGame.size(); i++)
	{
		if (allObjecjtsInGame[i] == object)
		{
			allObjecjtsInGame.erase(allObjecjtsInGame.begin() + i);
			return;
		}
	}
}

void ObjectsController::addBed(Bed* bed)
{
	beds.push_back(bed);
}

void ObjectsController::addRabbit(Rabbit* rabbit)
{
	rabbits.push_back(rabbit);
}


void ObjectsController::addCarrot(Carrot* carrot)
{
	carrots.push_back(carrot);
}

void ObjectsController::removeCarrot(Carrot* carrot)
{
	for (int i = 0; i < carrots.size(); i++)
	{
		if (carrots[i] == carrot)
		{
			carrots.erase(carrots.begin() + i);
			return;
		}
	}
}

void ObjectsController::drawObjects(ShaderProgram& phong)
{
	for (int i = 0; i < carrots.size(); i++)
	{
		carrots[i]->draw(phong);
	}
	for (int i = 0; i < beds.size(); i++)
	{
		beds[i]->draw(phong);
	}
}

void ObjectsController::drawRabbits(ShaderProgram& phong)
{
	for (int i = 0; i < rabbits.size(); i++)
	{
		rabbits[i]->draw(phong);
	}
}

Bed* ObjectsController::findNearestBed(glm::vec3 currentPosition)
{
	float distance = 9999999;
	Bed* nearest = nullptr;
	for (int i = 0; i < beds.size(); i++)
	{
		float newDist = calculateDistance(beds[i]->position, currentPosition);
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
void ObjectsController::killNearRabbit(glm::vec3 currentPosition)
{
	float minDistance = 4.f;
	for (int i = 0; i < rabbits.size(); i++)
	{
		float dist = calculateDistance(rabbits[i]->position, currentPosition);
		if (dist < minDistance)
		{
			rabbits.erase(rabbits.begin() + i);
			return;
		}
	}
}
void ObjectsController::eatCarrot()
{
	float minDistance = 3.f;
	for (int i = 0; i < rabbits.size(); i++)
	{
		for (int j = 0; j < carrots.size(); j++)
		{
			float dist = calculateDistance(rabbits[i]->position, carrots[j]->position);
			if (dist < minDistance) {
				rabbits[i]->carrot = nullptr;
				carrots.erase(carrots.begin() + j);
			}
		}
	}
}

float ObjectsController::calculateDistance(glm::vec3 p1, glm::vec3 p2)
{
	float distance = sqrt((p1.x - p2.x) * (p1.x - p2.x)
		+ (p1.y - p2.y) * (p1.y - p2.y)
		+ (p1.z - p2.z) * (p1.z - p2.z));

	return distance;
}

void ObjectsController::carrotsGrowing(float elapsed)
{
	for (int i = 0; i < carrots.size(); i++)
	{
		carrots[i]->grow(elapsed);
	}
}

void ObjectsController::runToCarrot()
{
	Rabbit* rabbit;
	float dist;
	for (int i = 0; i < rabbits.size(); i++)
	{
		rabbit = rabbits[i];
		if (carrots.size()<1)
			rabbit->runForward();
			

		else if (rabbit->carrot != nullptr)
			rabbit->runToCarrot();

		else
		{
			int carrotIndex = rand() % carrots.size();
			rabbit->carrot = carrots[carrotIndex];
			rabbit->runToCarrot();
			rabbit->rotate();
			
		}
	}
}

void ObjectsController::spawnRabbits(int quant)
{
	quant = quant / 4;
	int x[2] = { 0, 18 };
	int z[2] = { -3, 34 };
	float y = -2.4f;

	Rabbit* rabbit;
	for (int i = 0; i < quant; i++)
	{
		rabbit = new Rabbit(glm::vec3(x[0], y, z[0] + rand() % z[1]));
		rabbits.push_back(rabbit);

		rabbit = new Rabbit(glm::vec3(x[1], y, z[0] + rand() % z[1]));
		rabbits.push_back(rabbit);

		rabbit = new Rabbit(glm::vec3(x[0] + rand() % x[1], y, z[0]));
		rabbits.push_back(rabbit);

		rabbit = new Rabbit(glm::vec3(x[0] + rand() % x[1], y, z[1]));
		rabbits.push_back(rabbit);
	}

}
ObjectsController::ObjectsController()
{
	srand(time(0));
}