//
//  shader.hpp
//  clean-OpenGL-V2
//
//  Created by Robbe Titeca on 24/02/2021.
//

#ifndef shader_hpp
#define shader_hpp

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader{
public:
    unsigned int ID;
    
    Shader(const char* vPath, const char* fPath);
    void use();
    
    void setInt(const std::string &name, int value);
    void setFloat(const std::string &name, float value);
    void setBool(const std::string &name, bool value);
    void setVec3(const std::string &name, glm::vec3 value);
    void setMat4(const std::string &name, glm::mat4 value);
};

#endif /* shader_hpp */
