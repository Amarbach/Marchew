#pragma once
#include <iostream>
#include "Texture.h"
#include "Model.h"

class ModelsAndTextures {
public:
    static Model *carrot;
    static Texture* carrotTex;

    static void ModelsAndTexturesInit()
    {
        carrot = new Model("3Ds\\Carrot_Z3G.obj");
        carrotTex = new Texture("carrot_tex.png");
    }
};
