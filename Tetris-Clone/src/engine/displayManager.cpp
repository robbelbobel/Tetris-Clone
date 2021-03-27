//
//  displayManager.cpp
//  Tetris-Clone
//
//  Created by Robbe Titeca on 16/03/2021.
//

#include "displayManager.hpp"

DisplayManager::DisplayManager(ResourceManager* resourceManager, SpriteRenderer* spriteRenderer){
    // Assign Class Pointers
    DisplayManager::spriteRenderer = spriteRenderer;
    DisplayManager::resourceManager  = resourceManager;
}

void GameDisplayManager::renderBackground(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT){
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = glm::ortho(0.0f, (float) SCR_WIDTH, (float) SCR_HEIGHT, 0.0f, -1.0f, 1.0f);
    
    Texture* backgroundTexture = GameDisplayManager::resourceManager->gameBackgroundTexture;
    
    Shader* genericShader = GameDisplayManager::resourceManager->genericShader;
    
    float scaleY;
    float scaleX;
    
    float screenAspectRatio  = (float) SCR_WIDTH / (float) SCR_HEIGHT;
    float textureAspectRatio = (float) backgroundTexture->width / (float) backgroundTexture->height;
    
    if(screenAspectRatio <= textureAspectRatio){
        scaleY = SCR_HEIGHT;
        scaleX = textureAspectRatio * SCR_HEIGHT;
    }else{
        scaleX = SCR_WIDTH;
        scaleY = (1/textureAspectRatio) * SCR_WIDTH;
    }
    
    model = glm::scale(model, glm::vec3(scaleX, scaleY, 1.0f));
    
    GameDisplayManager::spriteRenderer->renderTexture(genericShader, backgroundTexture, model, projection);
}

void GameDisplayManager::renderTetromino(Tetromino* tetromino, GameBoard gameBoard, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT){
    glm::mat4 projection = glm::ortho(0.0f, (float) SCR_WIDTH, (float) SCR_HEIGHT, 0.0f, -1.0f, 1.0f);
    Texture* texture = GameDisplayManager::resourceManager->fragmentTexture;
    
    Shader* fragmentShader = GameDisplayManager::resourceManager->fragmentShader;
    
    int fragmentSize = floor(GameDisplayManager::fragmentSizeRatio * SCR_HEIGHT);
    
    
    int UI_margin_x = floor(GameDisplayManager::Board_marginRatio_x * SCR_WIDTH) - (fragmentSize * gameBoard.width)/2;
    int UI_margin_y = floor(GameDisplayManager::Board_marginRatio_y * SCR_HEIGHT) - (fragmentSize * gameBoard.height)/2;
    
    std::vector<Fragment*> fragments;
    std::vector<glm::mat4> models;
    std::vector<glm::mat4> projections;
    
    for(unsigned int i = 0; i < tetromino->rotations[tetromino->a_rot].fragments.size(); i++){
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(UI_margin_x + (tetromino->rotations[tetromino->a_rot].fragments[i].p_x + tetromino->posX) * fragmentSize, UI_margin_y + (gameBoard.height - (tetromino->rotations[tetromino->a_rot].fragments[i].p_y + tetromino->posY)) * fragmentSize, 0));
        model = glm::scale(model, glm::vec3(fragmentSize));
        
        models.push_back(model);
        fragments.push_back(&tetromino->rotations[tetromino->a_rot].fragments[i]);
        projections.push_back(projection);
    }
    
    GameDisplayManager::spriteRenderer->renderFragmentArray(fragmentShader, fragments, texture, models, projections);
    
}

void GameDisplayManager::renderBoardFrame(GameBoard gameBoard, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT){
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = glm::ortho(0.0f, (float) SCR_WIDTH, (float) SCR_HEIGHT, 0.0f, -1.0f, 1.0f);
    
    Texture* frameTexture = GameDisplayManager::resourceManager->gameFrameTexture;
    
    Shader* genericShader = GameDisplayManager::resourceManager->genericShader;
    
    float board_height =  (float) GameDisplayManager::fragmentSizeRatio * (float) SCR_HEIGHT * (float) gameBoard.height;
    
    float px_size = (float) board_height / ((float) frameTexture->height - ((float) GameDisplayManager::totalFrameHeightMargin));
    
    float frame_height = px_size * frameTexture->height;
    float frame_width  = px_size * frameTexture->width;
    
    float frame_x = GameDisplayManager::Board_marginRatio_x * SCR_WIDTH  - ((float) frame_width  / 2) - px_size * ((float) GameDisplayManager::totalFrameWidthMarginLeft / 2) + px_size * ((float) GameDisplayManager::totalFrameWidthMarginRight / 2);
    float frame_y = GameDisplayManager::Board_marginRatio_y * SCR_HEIGHT - ((float) frame_height / 2) + (GameDisplayManager::totalFrameHeightMargin / 2) * px_size;

    model = glm::translate(model, glm::vec3(frame_x, frame_y, 0.0f));
    model = glm::scale(model, glm::vec3(frame_width, frame_height, 1.0f));
    
    GameDisplayManager::spriteRenderer->renderTexture(genericShader, frameTexture, model, projection);
}

void GameDisplayManager::renderScore(unsigned int score, GameBoard gameBoard, unsigned SCR_WIDTH, unsigned int SCR_HEIGHT){
    glm::mat4 projection = glm::ortho(0.0f, (float) SCR_WIDTH, (float) SCR_HEIGHT, 0.0f, -1.0f, 1.0f);
    
    Shader* genericShader = GameDisplayManager::resourceManager->genericShader;
    
    int digitCount = 7;
    int digits[digitCount];
    
    // Precalculate size of a single fragment
    float fragmentSize = GameDisplayManager::fragmentSizeRatio * SCR_HEIGHT;
    
    // Calculate score number width, height and clearance
    float number_height = GameDisplayManager::scoreHeightRatio * SCR_HEIGHT;
    float number_width = ((float) GameDisplayManager::resourceManager->numberTexture[0]->width / (float) GameDisplayManager::resourceManager->numberTexture[0]->height) * number_height;
    float number_clearance = GameDisplayManager::numClearanceX * number_width;
    
    // Calculate score number position
    float number_x = GameDisplayManager::Board_marginRatio_x * SCR_WIDTH - (gameBoard.width / 2) * fragmentSize - GameDisplayManager::score_marginRatio_x * fragmentSize;
    float number_y = GameDisplayManager::Board_marginRatio_y * SCR_HEIGHT - (gameBoard.height / 2) * fragmentSize + number_height + GameDisplayManager::scoreClearanceY * SCR_HEIGHT;
    
    // Convert score to seperate integers
    for(unsigned int i = 0; i < digitCount; i++){
        digits[i] = ((int) floor(score / pow(10, i))) % 10;
    }
    
    // -----Number Loop-----
    std::vector<glm::mat4> projections;
    std::vector<glm::mat4> models;
    std::vector<Texture*> textures;
    
    for(unsigned int i = 0; i < digitCount; i++){
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(number_x - ((i + 1) * (number_width + number_clearance)), number_y, 0.0f));
        model = glm::scale(model, glm::vec3(number_width, number_height, 1.0f));
        
        // Push Uniforms
        projections.push_back(projection);
        models.push_back(model);
        textures.push_back(GameDisplayManager::resourceManager->numberTexture[digits[i]]);
    }
    
    GameDisplayManager::spriteRenderer->renderTextureArray(genericShader, textures, models, projections);
}

void GameDisplayManager::renderBoard(GameBoard gameBoard, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT){
    glm::mat4 projection = glm::ortho(0.0f, (float) SCR_WIDTH, (float) SCR_HEIGHT, 0.0f, -1.0f, 1.0f);
    
    Shader* fragmentShader = GameDisplayManager::resourceManager->fragmentShader;
    
    Texture* fragmentTexture = GameDisplayManager::resourceManager->fragmentTexture;
    
    int fragmentSize = floor(GameDisplayManager::fragmentSizeRatio * SCR_HEIGHT);
    
    int UI_margin_x = floor(GameDisplayManager::Board_marginRatio_x * SCR_WIDTH) - (fragmentSize * gameBoard.width)/2;
    int UI_margin_y = floor(GameDisplayManager::Board_marginRatio_y * SCR_HEIGHT) - (fragmentSize * gameBoard.height)/2;
    
    std::vector<Fragment*> fragments;
    std::vector<glm::mat4> models;
    std::vector<glm::mat4> projections;
    
    for(unsigned int y = 0; y < gameBoard.layout.size(); y++){
        for(unsigned int x = 0; x < gameBoard.layout[y].size(); x++){
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(UI_margin_x + x * fragmentSize, UI_margin_y + (gameBoard.height - y) * fragmentSize, 0));
            model = glm::scale(model, glm::vec3(fragmentSize));
            
            models.push_back(model);
            fragments.push_back(&gameBoard.layout[y][x]);
            projections.push_back(projection);
        }
    }
    
    GameDisplayManager::spriteRenderer->renderFragmentArray(fragmentShader, fragments, fragmentTexture, models, projections);
}

void GameDisplayManager::render(GameBoard gameBoard, Tetromino* tetromino, unsigned int score, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT){
    GameDisplayManager::renderBackground(SCR_WIDTH, SCR_HEIGHT);
    GameDisplayManager::renderBoardFrame(gameBoard, SCR_WIDTH, SCR_HEIGHT);
    
    GameDisplayManager::renderBoard(gameBoard, SCR_WIDTH, SCR_HEIGHT);
    GameDisplayManager::renderTetromino(tetromino, gameBoard, SCR_WIDTH, SCR_HEIGHT);
    
    GameDisplayManager::renderScore(score, gameBoard, SCR_WIDTH, SCR_HEIGHT);
}

void MenuDisplayManager::renderButtons(std::vector<Button*> buttons, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT){
    glm::mat4 projection = glm::ortho(0.0f, (float) SCR_WIDTH, (float) SCR_HEIGHT, 0.0f, -1.0f, 1.0f);
    
    Shader* genericShader = MenuDisplayManager::resourceManager->genericShader;
    
    std::vector<Texture*> buttonTextures;
    std::vector<glm::mat4> projections;
    std::vector<glm::mat4> models;
    
    for(unsigned int i = 0; i < buttons.size(); i++){
        glm::mat4 model = glm::mat4(1.0f);
        
        buttonTextures.push_back(buttons[i]->texture);
        
        projections.push_back(projection);
        
        model = glm::translate(model, glm::vec3(buttons[i]->getPosX(SCR_WIDTH), buttons[i]->getPosY(SCR_HEIGHT), 0.0f));
        model = glm::scale(model, glm::vec3(buttons[i]->getWidth(SCR_WIDTH), buttons[i]->getHeight(SCR_WIDTH), 1.0f));
        
        models.push_back(model);
    }
    
    MenuDisplayManager::spriteRenderer->renderTextureArray(genericShader, buttonTextures, models, projections);
}

void MenuDisplayManager::renderBackground(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT){
    glm::mat4 projection = glm::ortho(0.0f, (float) SCR_WIDTH, (float) SCR_HEIGHT, 0.0f, -1.0f, 1.0f);
    glm::mat4 model = glm::mat4(1.0f);
    
    Shader* genericShader = MenuDisplayManager::resourceManager->genericShader;
    
    Texture* backgroundtexture = MenuDisplayManager::resourceManager->menuBackgroundTexture;
    
    model = glm::translate(model, glm::vec3(0.0f));
    model = glm::scale(model, glm::vec3(SCR_WIDTH, SCR_HEIGHT, 1.0f));
    
    MenuDisplayManager::spriteRenderer->renderTexture(genericShader, backgroundtexture, model, projection);
}

void MenuDisplayManager::render(std::vector<Button*> buttons, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT){
    MenuDisplayManager::renderBackground(SCR_WIDTH, SCR_HEIGHT);
    MenuDisplayManager::renderButtons(buttons, SCR_WIDTH, SCR_HEIGHT);
}
