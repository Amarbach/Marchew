#pragma once
#include "include/glad/glad.h"

#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"

#include "include/assimp/Importer.hpp"
#include "include/assimp/scene.h"
#include "include/assimp/postprocess.h"

#include "Mesh.h"
#include "ShaderProgram.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

class Model
{
private:
	std::vector<Texture> textures_loaded;
	std::vector<Mesh> meshes;
	std::string directory;
	bool gammaCorrection;

	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type);

public:
	Model(std::string const& path);
	void Draw();
	void loadModel(std::string const& path);
};

