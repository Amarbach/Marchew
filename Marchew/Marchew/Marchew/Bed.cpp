#include "Bed.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "Texture.h"
#include <iostream>
#include <string>
#include "Carrot.h"
#include"ObjectsController.h"

using namespace std;

Bed::Bed()
{
   model = new Model("3Ds\\Soil_Z3G.obj");

   texture = new Texture("top-view-soil.jpg");
   texture->Load();

   position = glm::vec3(0.0f, 0.0f, 0.0f);
   scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

Bed::Bed(glm::vec3 _positon, glm::vec3 _scale) : Bed()
{
    position = _positon;
    scale = _scale;

    float carrotXpos = position.x - 0.2f;
    
    carrotPositions.push_back(glm::vec3(carrotXpos, -2.5f, position.z));
    carrotPositions.push_back(glm::vec3(carrotXpos, -2.5f, position.z-2.0f));
    carrotPositions.push_back(glm::vec3(carrotXpos, -2.5f, position.z+2.0f));

    hasCarrot.push_back(false);
    hasCarrot.push_back(false);
    hasCarrot.push_back(false);
}

void Bed::init()
{

}

void Bed::draw(ShaderProgram& phong)
{
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, position);
    transform = glm::scale(transform, scale);
    phong.setMat4("model", transform);
    texture->UseOn(GL_TEXTURE0);
    model->Draw();
}

void Bed::seedCarrot(ObjectsController &objectsController)
{
    for (int i = 0; i < 3; i++)
    {
        if (!hasCarrot[i])
        {
            hasCarrot[i] = true;
            Carrot* carrot = new Carrot(carrotPositions[i], glm::vec3(0.002f, 0.002f, 0.002f));
            carrot->connectedToBed = this;
            objectsController.addObject(carrot);

            return;
        }
    }
}