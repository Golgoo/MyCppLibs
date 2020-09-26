
#include <GL/glut.h>

namespace my{
namespace OGL::component{

    class DeltaTimer
    {
        private :
            float lastTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
            float current_time, deltaTime ;
        public:
            float tick(){
                current_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
                deltaTime = current_time - lastTime;
                lastTime = current_time ;
                return deltaTime ;
            }
    };
}
}