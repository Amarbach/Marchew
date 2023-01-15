#include "Carrot.h"
#include "Texture.h"
#include "Model.h"

Carrot::Carrot()
{
    model = new Model("3Ds\\Carrot_Z3G.obj");

    texture = new Texture("carrot_tex.png");
    texture->Load();
}

void Carrot::init()
{

}

void Carrot::draw(ShaderProgram& phong)
{
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(1.0f, -1.0f, -1.0f));
    transform = glm::scale(transform, glm::vec3(0.001f, 0.001f, 0.001f));
    phong.setMat4("model", transform);
    //texture->UseOn(GL_TEXTURE0);
    model->Draw();
}