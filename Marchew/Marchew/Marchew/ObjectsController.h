#pragma once
#include "Object.h"
#include <vector>

class ObjectsController
{
public:
	void addObject(Object* object);
	void drawObjects(ShaderProgram& phong);
private:
	std::vector<Object*> allObjecjtsInGame;
};

