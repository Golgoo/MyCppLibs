#pragma once

#include <glm/glm.hpp>

#include <my/OGL/component/movable.hpp>

namespace my{
namespace OGL::component{

class Camera : public Movable
{
    public:
        Camera(glm::vec3 startingPos = glm::vec3(0.0f, 0.0f, 0.0f), bool ableToFly = false);
        glm::mat4 getLookAtMat4() const;
        glm::vec3 getPosition() const;
};

}
}
