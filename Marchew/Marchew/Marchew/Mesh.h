#pragma once
#include "include/glad/glad.h"
#include "ShaderProgram.h"
#include <vector>
#include "Texture.h"
#include "include/glad/glad.h"

struct Vertex 
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
};

class Mesh
{
private:
	std::vector<Vertex>       vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture>      textures;
	unsigned int VAO, VBO, EBO, lightVAO;

public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void Load();
	void Draw();
};

