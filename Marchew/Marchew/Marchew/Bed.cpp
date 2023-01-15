#include "Bed.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "Texture.h"
#include <iostream>
#include <string>

using namespace std;

Bed::Bed()
{
   model = new Model("3Ds\\Soil_Z3G.obj");

   texture = new Texture("top-view-soil.jpg");
   texture->Load();
}

void Bed::init()
{

}

void Bed::draw(ShaderProgram& phong)
{
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(2.0f, -1.8f, -1.0f));
    transform = glm::scale(transform, glm::vec3(0.002f, 0.002f, 0.002f));
    phong.setMat4("model", transform);
    texture->UseOn(GL_TEXTURE0);
    model->Draw();
}