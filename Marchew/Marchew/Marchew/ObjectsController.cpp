#include "ObjectsController.h"
#include <vector>

void ObjectsController::addObject(Object* object)
{
	allObjecjtsInGame.push_back(object);
}

void ObjectsController::drawObjects(ShaderProgram& phong)
{
	for (int i = 0; i < allObjecjtsInGame.size(); i++)
	{
		allObjecjtsInGame[i]->draw(phong);
	}
}