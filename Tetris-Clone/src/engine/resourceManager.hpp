//
//  resourceManager.hpp
//  Tetris-Clone
//
//  Created by Robbe Titeca on 16/03/2021.
//

#ifndef resourceManager_hpp
#define resourceManager_hpp

#include <stdio.h>
#include <string>
#include "spriteRenderer.hpp"

class ResourceManager{
private:
    SpriteRenderer* spriteRenderer;
public:
    ResourceManager(SpriteRenderer* spriteRenderer, std::string& assetPath, std::string& shaderPath);
    
    //-----TEXTURES-----
    Texture* fragmentTexture;
    Texture* gameFrameTexture;
    Texture* playButtonTexture;
    
    Texture* numberTexture[10];
    
    // Background Textures
    Texture* gameBackgroundTexture;
    Texture* menuBackgroundTexture;
    
    //-----SHADERS-----
    Shader *fragmentShader;
    Shader *genericShader;
};

#endif /* resourceManager_hpp */
