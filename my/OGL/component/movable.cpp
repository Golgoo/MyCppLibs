#include <my/OGL/component/movable.hpp>

using namespace my::OGL::component;

Movable::Movable(glm::vec3 startingPosition, bool ableToFly): position(startingPosition), ableToFly(ableToFly) 
{

}

void Movable::setAbleToFly(bool ableToFly)
{
    this->ableToFly = ableToFly ;
}

void Movable::moveFront(const float speed)
{
    updatePosition(this->position + speed * this->target);
}

void Movable::moveBack(const float speed)
{
    updatePosition(this->position - speed * this->target);
}

void Movable::moveRight(const float speed)
{
    updatePosition(this->position + glm::normalize(glm::cross(this->target, this->worldUp)) * speed);
}

void Movable::moveLeft(const float speed)
{
    updatePosition(this->position - glm::normalize(glm::cross(this->target, this->worldUp)) * speed);
}

void Movable::updatePosition(const glm::vec3 newPosition)
{
    if(this->ableToFly){
        this->position = newPosition ;
    }
    else{
        float currentY = this->position.y ;
        this->position = newPosition ;
        this->position.y = currentY ;
    }
}

void Movable::setDirection(const float yaw, const float pitch)
{
    this->yaw = yaw ;
    this->pitch = pitch ;

    if(this->pitchClampEnable){
        clampPitch();
    }
    if(this->yawClampEnable){
        clampYaw();
    }

    glm::vec3 direction ;
    direction.x = cos(glm::radians(yaw));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw));
    if(this->ableToFly) 
        direction.z *= cos(glm::radians(pitch));
    this->target = glm::normalize(direction);
}

void Movable::rotate(const float xOffset, const float yOffset)
{
    this->setDirection(xOffset + this->yaw, yOffset + this->pitch);
}

void Movable::clampPitch()
{
    if(this->pitch < this->pitchClampMin){
        this->pitch = this->pitchClampMin ;
    }
    if(this->pitch > this->pitchClampMax){
        this->pitch = this->pitchClampMax ;
    }
}

void Movable::clampYaw()
{
    if(this->yaw < this->yawClampMin){
        this->yaw = this->yawClampMin ;
    }
    if(this->yaw > this->yawClampMax){
        this->yaw = this->yawClampMax ;
    }
}

void Movable::activePitchClamp(const bool active)
{
    this->pitchClampEnable = active;
}
void Movable::activeYawClamp(const bool active)
{
    this->yawClampEnable = active ;
}

void Movable::setPitchClamp(const float min, const float max)
{
    this->pitchClampMin = min ;
    this->pitchClampMax = max ;
}
void Movable::setYawClamp(const float min, const float max)
{
    this->yawClampMin = min ;
    this->yawClampMax = max ;
}