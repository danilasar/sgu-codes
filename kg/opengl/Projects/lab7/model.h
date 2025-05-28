#pragma once
#include "path.h"
#include <glm/glm.hpp>

class model {
public:
    std::vector<path> paths;
    glm::mat4 transform;
    
    model(std::vector<path> p, glm::mat4 t) : paths(p), transform(t) {}
};
