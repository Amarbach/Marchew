#include "Rabbit.h"
#include "Texture.h"
#include "Model.h"


Rabbit::Rabbit()
{
    model = new Model("3Ds\\Bunny.obj");

    texture = new Texture("carrot_tex.png");
    texture->Load();

    position = glm::vec3(0.0f, 0.0f, 0.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
    carrot = nullptr;
    speed = 0.01;
}

Rabbit::Rabbit(glm::vec3 _positon, float _angleY) : Rabbit()
{
    position = _positon;
    angleY = _angleY;
}

void Rabbit::init()
{
}

void Rabbit::draw(ShaderProgram& phong){

    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, position);
    transform = glm::rotate(transform, angleY, glm::vec3(0,1,0));
    transform = glm::scale(transform, scale);
    phong.setMat4("model", transform);
    texture->UseOn(GL_TEXTURE0);
    model->Draw();
}

void Rabbit::runToCarrot()
{
    if (carrot == nullptr)
        return;
    
    float distX = carrot->position.x - position.x;
    float distZ = carrot->position.z - position.z;
    float dist = CalculateCarrotDistance();
    angleY = asin(distX / dist);
    position.x += speed * distX / dist;
    position.z += speed *distZ/dist;
}

void Rabbit::runForward()
{
    position.x += speed;
    position.z += speed;
}


float Rabbit::CalculateCarrotDistance()
{
    if (carrot == nullptr)
        return 1;
   
    glm::vec3 p1 = position;
    glm::vec3 p2 = carrot->position;
    float distance = sqrt((p1.x - p2.x) * (p1.x - p2.x)
        + (p1.y - p2.y) * (p1.y - p2.y)
        + (p1.z - p2.z) * (p1.z - p2.z));

    return distance;
}

Rabbit::~Rabbit()
{
    delete model;
    delete texture;
}