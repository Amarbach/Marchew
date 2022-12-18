#include "Texture.h"


Texture::Texture(std::string filename)
{
	this->filename = filename;
    this->wrapS = GL_REPEAT;
    this->wrapT = GL_REPEAT;
    this->minFilter = GL_LINEAR;
    this->maxFilter = GL_LINEAR;
}

void Texture::Load()
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrapS);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrapT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->maxFilter);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    //stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    std::string texturesPath = "textures\\";
    unsigned char* data = stbi_load((texturesPath + filename).c_str(), &width, &height, &nrChannels, 0);
    unsigned int colorFormat = GL_RGB;
    if (nrChannels == 4) colorFormat = GL_RGBA;
    else if (nrChannels == 3) colorFormat = GL_RGB;
    else if (nrChannels == 1) colorFormat = GL_RED;
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, colorFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void Texture::setWrapTypeS(unsigned int type)
{
    this->wrapS = type;
}

void Texture::setWrapTypeT(unsigned int type)
{
    this->wrapT = type;
}

void Texture::setMinFilter(unsigned int filter)
{
    this->minFilter = filter;
}

void Texture::setMaxFilter(unsigned int filter)
{
    this->maxFilter = filter;
}

void Texture::UseOn(unsigned int texUnit)
{
    glActiveTexture(texUnit);
    glBindTexture(GL_TEXTURE_2D, ID);
    glActiveTexture(GL_TEXTURE0);
}

std::string Texture::getFilename()
{
    return filename;
}
