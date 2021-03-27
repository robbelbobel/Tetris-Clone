//
//  shader.cpp
//  clean-OpenGL-V2
//
//  Created by Robbe Titeca on 24/02/2021.
//

#include "shader.hpp"
Shader::Shader(const char* vPath, const char* fPath){
    // Copyright Joey De Vries - https://www.learnopengl.com/
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vPath);
        fShaderFile.open(fPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderSource = vertexCode.c_str();
    const char* fShaderSource = fragmentCode.c_str();
    
    //-----Create Shaders-----
    unsigned int vertexShader, fragmentShader;
    // Vertex Shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderSource, NULL);
    glCompileShader(vertexShader);
    // Error Checking
    int succes;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &succes);
    if(!succes){
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Failed to compile vertex shader! InfoLog: " << infoLog << std::endl;
    }
    // Fragment Shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &succes);
    if(!succes){
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Failed to compile fragment shader! InfoLog: " << infoLog << std::endl;
    }
    // Shader Program
    Shader::ID = glCreateProgram();
    glAttachShader(Shader::ID, vertexShader);
    glAttachShader(Shader::ID, fragmentShader);
    glLinkProgram(Shader::ID);
    
    glGetProgramiv(Shader::ID, GL_LINK_STATUS, &succes);
    if(!succes){
        char infoLog[512];
        glGetProgramInfoLog(Shader::ID, 512, NULL, infoLog);
        std::cout << "Failed to link shader program! InfoLog: " << infoLog << std::endl;
    }
    
    glDetachShader(Shader::ID, vertexShader);
    glDetachShader(Shader::ID, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use(){
    glUseProgram(Shader::ID);
}

void Shader::setInt(const std::string &name, int value){
    glUniform1i(glGetUniformLocation(Shader::ID, name.c_str()), value);
}
void Shader::setMat4(const std::string &name, glm::mat4 value){
    glUniformMatrix4fv(glGetUniformLocation(Shader::ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
void Shader::setVec3(const std::string &name, glm::vec3 value){
    glUniform3fv(glGetUniformLocation(Shader::ID, name.c_str()), 1, glm::value_ptr(value));
}
