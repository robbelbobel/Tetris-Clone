//
//  resourceManager.cpp
//  Tetris-Clone
//
//  Created by Robbe Titeca on 16/03/2021.
//

#include "resourceManager.hpp"

ResourceManager::ResourceManager(SpriteRenderer* spriteRenderer, std::string& assetPath, std::string& shaderPath){
    //-----LOAD TEXTURES-----
    ResourceManager::fragmentTexture = ResourceManager::spriteRenderer->loadTexture(assetPath + "game/fragment.png");
    ResourceManager::gameFrameTexture = ResourceManager::spriteRenderer->loadTexture(assetPath + "game/frame.png");
    ResourceManager::playButtonTexture = ResourceManager::spriteRenderer->loadTexture(assetPath + "menu/playButton.png");
    
    ResourceManager::gameBackgroundTexture = ResourceManager::spriteRenderer->loadTexture(assetPath + "game/background.png");
    ResourceManager::menuBackgroundTexture = ResourceManager::spriteRenderer->loadTexture(assetPath + "menu/background.png");
    
    for(unsigned int i = 0; i < 10; i++){
        ResourceManager::numberTexture[i] = ResourceManager::spriteRenderer->loadTexture(assetPath + "characters/" + std::to_string(i) + ".png");
    }
    
    //-----LOAD SHADERS-----
    std::string genericVertShaderPath = shaderPath+ "generic.vert", genericFragShaderPath = shaderPath + "generic.frag";
    std::string fragmentVertShaderPath = shaderPath+ "fragment.vert", fragmentFragShaderPath = shaderPath + "fragment.frag";
    
    ResourceManager::genericShader = new Shader(genericVertShaderPath.c_str(), genericFragShaderPath.c_str());
    ResourceManager::fragmentShader = new Shader(fragmentVertShaderPath.c_str(), fragmentFragShaderPath.c_str());
}
