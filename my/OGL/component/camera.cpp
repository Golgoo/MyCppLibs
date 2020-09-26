#include <my/OGL/component/camera.hpp>

#include <glm/gtc/matrix_transform.hpp>

using namespace my::OGL::component;

Camera::Camera(glm::vec3 startingPos, bool ableToFly): Movable(startingPos, ableToFly)
{

}

glm::mat4 Camera::getLookAtMat4() const
{
    return glm::lookAt(
        Movable::position,
        Movable::position + Movable::target,
        Movable::worldUp
    );
}

glm::vec3 Camera::getPosition() const
{
    return Movable::position ;
}