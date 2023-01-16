#include "Carrot.h"
#include "Texture.h"
#include "Model.h"

Carrot::Carrot()
{
    model = new Model("3Ds\\Carrot_Z3G.obj");

    texture = new Texture("carrot_tex.png");
    texture->Load();

    position = glm::vec3(0.0f, 0.0f, 0.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

Carrot::Carrot(glm::vec3 _positon, glm::vec3 _scale) : Carrot()
{
    position = _positon;
    scale = _scale;
}

void Carrot::init()
{
}

void Carrot::draw(ShaderProgram& phong)
{
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, position);
    transform = glm::scale(transform, scale);
    phong.setMat4("model", transform);
    texture->UseOn(GL_TEXTURE0);
    model->Draw();
}