#pragma once

#include <glm/glm.hpp>

namespace my{
namespace OGL::component{

    class Movable
    {
        private :
            bool ableToFly ;
            bool pitchClampEnable = false ;
            bool yawClampEnable = false ;
            float pitchClampMin, pitchClampMax ;
            float yawClampMin, yawClampMax ;

        public :
            Movable(glm::vec3 startingPosition = glm::vec3(0.0f, 0.0f, 3.0f), bool ableToFly = false);
            void setAbleToFly(bool ableToFly);

        protected:
            glm::vec3 position ;
            glm::vec3 target = glm::vec3(0.0f, 0.0f, -1.0f);
            glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
            float yaw = -90.0f, pitch ;

        public:
            void moveFront(const float speed) ;
            void moveBack(const float speed) ;
            void moveRight(const float speed) ;
            void moveLeft(const float speed) ;
            void setPitchClamp(const float min, const float max);
            void activePitchClamp(const bool active);
            void activeYawClamp(const bool active);
            void setYawClamp(const float min, const float max);
            void setDirection(const float yaw, const float pitch);
            void rotate(const float xOffset, const float yOffset);

            inline glm::vec3 getPosition(){return position ; };
        private:
            void clampYaw();
            void clampPitch();
            void updatePosition(const glm::vec3 newPosition);
    };
    
} 
}
