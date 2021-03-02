//
//  main.cpp/Users/robbetiteca/projects/Tetris-Clone/Tetris-Clone/main.cpp
//  Tetris-Clone
//
//  Created by Robbe Titeca on 27/02/2021.
//
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
#include "game.hpp"

//-----SCREEN VARS-----
unsigned int SCR_WIDTH = 800, SCR_HEIGHT = 450;

//-----FUNCTION PROTOYPES-----
void inputHandler(GLFWwindow* window);
// Callback Functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main(int argc, const char * argv[]) {
    //-----INITIALIZE GLFW-----
    glfwInit();
    // Window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Tetris 8-BIT", NULL, NULL);
    if(!window){
        std::cout << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    // Set Callback Functions
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    //-----INITIALIZE GLAD-----
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD!" << std::endl;
        return -1;
    }
    glViewport(SCR_WIDTH, SCR_HEIGHT, 0, 0);
    
    // Create Game Object
    Game game(window);
    
    //-----MAIN LOOP-----
    while(!glfwWindowShouldClose(window)){
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        game.update(SCR_WIDTH, SCR_HEIGHT);
        
        int glErr = glGetError();
        if(glErr != GL_NO_ERROR){
            std::cout << "OpenGL ran into an error! Error: "<< glErr << std::endl;
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
    glViewport(width, height, 0, 0);
}
