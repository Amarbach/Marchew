#include "Rabbit.h"


Rabbit::Rabbit()
{
    model = new Model("3Ds\\Bunny.obj");

    texture = new Texture("rabbit-fur.jpg");
    texture->Load();

    position = glm::vec3(0.0f, 0.0f, 0.0f);
    scale = glm::vec3(0.6f, 0.6f, 0.6f);
    carrot = nullptr;
    speed = 0.01;
    angleY = 0;
}

Rabbit::Rabbit(glm::vec3 _positon) : Rabbit()
{
    position = _positon;
}

void Rabbit::init()
{
}


void Rabbit::draw(ShaderProgram& phong){

    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, position);
    transform = glm::scale(transform, scale); transform = glm::rotate(transform, angleY, glm::vec3(0, 1, 0));
    //transform = glm::scale(transform, scale); transform = glm::rotate(transform, (float)std::numbers::pi, glm::vec3(0, 1, 0));
    phong.setMat4("model", transform);
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
    float dist = carrotDistance();
    position.x += speed * distX / dist;
    position.z += speed * distZ / dist;
}

void Rabbit::runForward()
{
    position.z -= speed*1.5;
    position.x -= speed*1.5;
    angleY = std::numbers::pi/4;
}

float::Rabbit::carrotAngle() {
    float distX = position.x -carrot->position.x;
    float distZ = position.z - carrot->position.z;
    return atan(distX / distZ);
}

void::Rabbit::rotate() {
    float angle = carrotAngle();
    angleY =angle+std::numbers::pi;
}

float Rabbit::carrotDistance()
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