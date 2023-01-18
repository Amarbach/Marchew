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
    isGrowing = true;
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

void Carrot::grow(float elapsed)
{
    if (!isGrowing)
    {
        return;
    }

    growingTime -= (elapsed * 1200.0f);
    float newYPos = naive_lerp(-2.5f, -2.9f, growingTime / 80000.0f);
    position = glm::vec3(position.x, newYPos, position.z);

    if (growingTime <= 0)
    {
        isGrowing = false;
    }
}

float Carrot::naive_lerp(float a, float b, float t)
{
    return a + t * (b - a);
}

Carrot::~Carrot()
{
    delete model;
    delete texture;
}