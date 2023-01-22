#include <iostream>
#include <vector>

#include "include/glad/glad.h"
#include "include/GLFW/glfw3.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"

#include "Camera.h"
#include "ShaderProgram.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"
#include "Mesh.h"
#include "Model.h"
#include "DayCycle.h"
#include "Bed.h"
#include "Carrot.h"
#include "ObjectsController.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera mainCamera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f, 0.1f, 100.0f, SCR_HEIGHT, SCR_WIDTH, PERSPECTIVE);
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

bool firstMouse = true;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;

bool toggleWireframe = false;

DayCycle cycle;
ObjectsController objectController = ObjectsController();


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void seedCarrot()
{
    if (!cycle.isDay())
    {
        return;
    }

    Bed* bed = objectController.findNearestBed(mainCamera.getPosition());
    if (bed == nullptr)
    {
        return;
    }
    bed->seedCarrot(objectController);
}

void takeCarrot()
{
    Bed* bed = objectController.findNearestBed(mainCamera.getPosition());
    if (bed == nullptr)
    {
        return;
    }
    bed->takeCarrot(objectController);
}

bool seedKey = false;
bool takeKey = false;

void processInput(GLFWwindow* window)
{
    float cameraSpeed = static_cast<float>(2.5 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        mainCamera.moveForward(cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        mainCamera.moveForward(-cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        mainCamera.moveSide(-cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        mainCamera.moveSide(cameraSpeed);
    //if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
       // mainCamera.moveUp(cameraSpeed);
   // if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
      //  mainCamera.moveUp(-cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        seedKey = true;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        takeKey = true;

    if (seedKey && glfwGetKey(window, GLFW_KEY_Q) == GLFW_RELEASE)
    {
        seedKey = false;
        seedCarrot();
    }
    if (takeKey && glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE)
    {
        takeKey = false;
        takeCarrot();
    } 
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
    {
        toggleWireframe = !toggleWireframe;
        if (toggleWireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    mainCamera.orient(xoffset, yoffset);
}
void drawSun() 
{
    //glutSolidSphere(1.25, 100, 100);
}

Mesh drawFloor()
{
    std::vector<Vertex> floor;
    floor.push_back({ glm::vec3(-100.0f, -3.0f, 100.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(10.0f, 0.0f) });
    floor.push_back({ glm::vec3(0.0f, -3.0f, 100.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) });
    floor.push_back({ glm::vec3(0.0f, -3.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 10.0f) });
    floor.push_back({ glm::vec3(-100.0f, -3.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(10.0f, 10.0f) });

    floor.push_back({ glm::vec3(0.0f, -3.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(10.0f, 0.0f) });
    floor.push_back({ glm::vec3(100.0f, -3.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) });
    floor.push_back({ glm::vec3(100.0f, -3.0f, -100.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 10.0f) });
    floor.push_back({ glm::vec3(0.0f, -3.0f, -100.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(10.0f, 10.0f) });

    floor.push_back({ glm::vec3(-100.0f, -3.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(10.0f, 0.0f) });
    floor.push_back({ glm::vec3(0.0f, -3.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) });
    floor.push_back({ glm::vec3(0.0f, -3.0f, -100.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 10.0f) });
    floor.push_back({ glm::vec3(-100.0f, -3.0f, -100.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(10.0f, 10.0f) });

    floor.push_back({ glm::vec3(0.0f, -3.0f, 100.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(10.0f, 0.0f) });
    floor.push_back({ glm::vec3(100.0f, -3.0f, 100.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) });
    floor.push_back({ glm::vec3(100.0f, -3.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 10.0f) });
    floor.push_back({ glm::vec3(0.0f, -3.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(10.0f, 10.0f) });

    std::vector<unsigned int> indices;
    indices.push_back(3);
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(3);

    indices.push_back(7);
    indices.push_back(4);
    indices.push_back(5);
    indices.push_back(5);
    indices.push_back(6);
    indices.push_back(7);

    indices.push_back(11);
    indices.push_back(8);
    indices.push_back(9);
    indices.push_back(9);
    indices.push_back(10);
    indices.push_back(11);

    indices.push_back(15);
    indices.push_back(12);
    indices.push_back(13);
    indices.push_back(13);
    indices.push_back(14);
    indices.push_back(15);

    std::vector<Texture> texs;
    Mesh ground(floor, indices, texs);
    ground.Load();

    return ground;
}

int main()
{
    //inicjalizacja
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Marchew", NULL, NULL);
    if (window == NULL) {
        std::cout << "error\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Mesh ground = drawFloor();

    //ładowanie shaderów
    ShaderProgram shader("vertex.vs", "fragment.fs");
    ShaderProgram phong("phong1.vs", "phong1.fs");
    ShaderProgram shaderSun("sun.vs", "sun.fs");

    //ładowanie modeli
    Model sun = Model("3Ds\\Sun.obj");

    //ładowanie tekstur i wrzucanie ich do openGL/na kartę graficzna;
    Texture sunTex = Texture("sun.jpg");
    sunTex.Load();
    Texture soilTex = Texture("top-view-soil.jpg");
    soilTex.Load();

    cycle.setTimeScale(1200.0f);
    
    //włączenie testu głębi
    glEnable(GL_DEPTH_TEST);
   
    //tworzymy poletko
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            Bed* bed = new Bed(glm::vec3(2.0f + (i * 3.5f), -1.8f, -1.0f + (j*8.3f)), glm::vec3(0.002f, 0.002f, 0.002f));
            objectController.addObject(bed);
            objectController.addBed(bed);
        }
    }
    objectController.spawnRabbits(8);
    while (!glfwWindowShouldClose(window))
    {
        //sterowanie czasowe i wyznaczanie deltaTime

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);
        float vTime = (float)(glfwGetTime());
        glm::vec3 lightPos = 100.0f * cycle.getSunDirection();
        cycle.update(deltaTime);
        objectController.carrotsGrowing(deltaTime);

        //czyszczenie
        glClearColor(0.1f, 0.3f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //wrzucenie tekstur na jednostki teksturowe
      
        glm::vec3 lightColor = glm::vec3(1.0, 1.0, 1.0) * cycle.getSunlightIntensity();
        
        //włączenie shadera i przekazanie macierzy projekcji, koloru światła, pozycji światła i pozycji obserwatora
        phong.use();
        phong.setMat4("projection", mainCamera.getProjectionMtx());
        phong.setInt("texture1", 0);
        phong.setVec3("lightColor", lightColor);
        phong.setVec3("lightPos", lightPos);
        phong.setVec3("viewPos", mainCamera.getPosition());
        //ustawianie macierzy view kamery(pozycja, rotacja i up)
        phong.setMat4("view", mainCamera.getViewMtx());

        //wyznaczenie pozycji, rotacji i skali zająca
        
        glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //transform = glm::translate(transform, glm::vec3(0.0f, sin(vTime)/2.0, 0.0f));
    /*    transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, -1.0f));
        transform = glm::rotate(transform, vTime, glm::vec3(0.0f, 1.0f, 0.0f));
        transform = glm::scale(transform, glm::vec3(0.1f, 0.1f, 0.1f));
        phong.setMat4("model", transform);*/
  
        //rysujemy obiekty
        objectController.drawObjects(phong);
       
        //transform = glm::mat4(1.0f);
        soilTex.UseOn(GL_TEXTURE0);
        phong.setMat4("model", glm::mat4(1.0f));
        ground.Draw();

        //sun
        shaderSun.use();
        shaderSun.setMat4("projection", mainCamera.getProjectionMtx());
        shaderSun.setMat4("view", mainCamera.getViewMtx());
       
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, lightPos);
        transform = glm::scale(transform, glm::vec3(0.005f, 0.005f, 0.005f));
        shaderSun.setMat4("model", transform);

        sunTex.UseOn(GL_TEXTURE0);
        sunTex.UseOn(GL_TEXTURE1);
        if (cycle.isDay()) sun.Draw();
        else
        {
            objectController.EatCarrot();
            objectController.drawRabbits(phong);
            objectController.runToCarrot(1.f);
            objectController.KillNearRabbit(mainCamera.getPosition());
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}