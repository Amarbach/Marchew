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

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera mainCamera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f, 0.1f, 100.0f, SCR_HEIGHT, SCR_WIDTH, PERSPECTIVE);
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

bool firstMouse = true;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;

bool toggleWireframe = false;


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

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
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        mainCamera.moveUp(cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        mainCamera.moveUp(-cameraSpeed);
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

    std::vector<Vertex> floor;
    floor.push_back({ glm::vec3(-2.0f,  0.0f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f) });
    floor.push_back({ glm::vec3(0.0f,   0.0f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) });
    floor.push_back({ glm::vec3(0.0f,  0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f) });
    floor.push_back({ glm::vec3(-2.0f,  0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f) });
    std::vector<unsigned int> indices;
    indices.push_back(3);
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(3);
    std::vector<Texture> texs;
    Mesh ground(floor, indices, texs);
    ground.Load();

    //ładowanie shaderów
    ShaderProgram shader("vertex.vs", "fragment.fs");
    ShaderProgram phong("phong1.vs", "phong1.fs");
    ShaderProgram shaderSun("sun.vs", "sun.fs");

    //ładowanie zająca
    Model test1("3Ds\\Bunny.obj");
    Model marchew("3Ds\\Carrot_Z3G.obj");
    Model sun("3Ds\\Sun.obj");
    Model plot("3Ds\\Soil_Z3G.obj");


    //ładowanie tekstur i wrzucanie ich do openGL/na kartę graficzną
    Texture tex1("tex1.jpg");
    tex1.Load();
    Texture tex2("tex2.jpg");
    tex2.Load();
    Texture grass("grass.jpg");
    grass.Load();
    Texture sunTex("sun.jpg");
    sunTex.Load();
    Texture marchewTex("carrot_tex.png");
    marchewTex.Load();
    Texture soilTex("top-view-soil.jpg");
    soilTex.Load();
    
    
    //włączenie testu głębi
    glEnable(GL_DEPTH_TEST);

    glm::vec3 lightPos;
   
    while (!glfwWindowShouldClose(window))
    {
        //sterowanie czasowe i wyznaczanie deltaTime
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);
        float vTime = (float)(glfwGetTime())/10.0f;
        lightPos = glm::vec3(10.0f * cos(vTime), 10.0f * sin(vTime), -10.0f);

        //czyszczenie
        glClearColor(0.1f, 0.3f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //wrzucenie tekstur na jednostki teksturowe
        tex1.UseOn(GL_TEXTURE0);
        
        //włączenie shadera i przekazanie macierzy projekcji, koloru światła, pozycji światła i pozycji obserwatora
        phong.use();
        phong.setMat4("projection", mainCamera.getProjectionMtx());
        phong.setInt("texture1", 0);
        phong.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        phong.setVec3("lightPos", lightPos);
        phong.setVec3("viewPos", mainCamera.getPosition());
        //ustawianie macierzy view kamery(pozycja, rotacja i up)
        phong.setMat4("view", mainCamera.getViewMtx());

        //wyznaczenie pozycji, rotacji i skali zająca
        
        glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //transform = glm::translate(transform, glm::vec3(0.0f, sin(vTime)/2.0, 0.0f));
        transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, -1.0f));
        //transform = glm::rotate(transform, vTime, glm::vec3(0.0f, 1.0f, 0.0f));
        transform = glm::scale(transform, glm::vec3(0.1f, 0.1f, 0.1f));
        phong.setMat4("model", transform);

        //rysowanie zająca
        test1.Draw();

        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(1.0f, -1.0f, -1.0f));
        transform = glm::scale(transform, glm::vec3(0.01f, 0.01f, 0.01f));
        phong.setMat4("model", transform);
        //marchewTex.UseOn(GL_TEXTURE0);
        marchew.Draw();

        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(2.0f, 1.0f, -1.0f));
        transform = glm::scale(transform, glm::vec3(0.01f, 0.01f, 0.01f));
        phong.setMat4("model", transform);
        //soilTex.UseOn(GL_TEXTURE0);
        plot.Draw();

        //transform = glm::mat4(1.0f);
        phong.setMat4("model", glm::mat4(1.0f));
        ground.Draw();

        //sun
        shaderSun.use();
        shaderSun.setMat4("projection", mainCamera.getProjectionMtx());
        shaderSun.setMat4("view", mainCamera.getViewMtx());
       
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, lightPos);
        transform = glm::scale(transform, glm::vec3(0.001f, 0.001f, 0.001f));
        shaderSun.setMat4("model", transform);

        sunTex.UseOn(GL_TEXTURE0);
        sunTex.UseOn(GL_TEXTURE1);
        sun.Draw();


        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}