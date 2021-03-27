//
//  spriteRenderer.hpp
//  Tetris-Clone
//
//  Created by Robbe Titeca on 28/02/2021.
//

#ifndef spriteRenderer_hpp
#define spriteRenderer_hpp

#include "shader.hpp"
#include <string>
#include <vector>
#include "../../include/stb_image.h"

#include "tetromino.hpp"
#include "button.hpp"

struct Texture{
    unsigned int ID;
    unsigned int width;
    unsigned int height;
    unsigned int nrChannels;
};

class SpriteRenderer{
private:
    unsigned int VAO, VBO;
    
public:
    SpriteRenderer();
    
    Texture* loadTexture(std::string path);
    
    void renderTextureArray(Shader* shader, std::vector<Texture*> textures, std::vector<glm::mat4> models, std::vector<glm::mat4> projections);
    void renderFragmentArray(Shader* shader, std::vector<Fragment*> fragments, Texture* texture, std::vector<glm::mat4> models, std::vector<glm::mat4> projections);
    void renderTexture(Shader* shader, Texture* texture, glm::mat4 model, glm::mat4 projection);
};

#endif /* spriteRenderer_hpp */
