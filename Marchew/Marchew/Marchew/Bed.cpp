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

   position = glm::vec3(0.0f, 0.0f, 0.0f);
   scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

Bed::Bed(glm::vec3 _positon, glm::vec3 _scale) : Bed()
{
    position = _positon;
    scale = _scale;
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