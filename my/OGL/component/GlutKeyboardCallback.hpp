#pragma once

#include <functional>

namespace my{
namespace OGL::component{

    class GlutKeyboardCallback{
        private:
            static std::function<void(unsigned char, int, int)> keyPressedCallback ;
            static std::function<void(unsigned char, int, int)> keyUpCallback ;
        public:
            static void setKeyPressedCallback(std::function<void(unsigned char, int, int)> keyPressedCallback){
                GlutKeyboardCallback::keyPressedCallback = keyPressedCallback ;
            }
            static void setKeyUpCallback(std::function<void(unsigned char, int, int)> keyUpCallback){
                GlutKeyboardCallback::keyUpCallback = keyUpCallback ;
            }
            static void keyUpGlutCallback(unsigned char key, int x, int y){
                GlutKeyboardCallback::keyUpCallback(key, x, y);
            }
            static void keyPressedGlutCallback(unsigned char key, int x, int y){
                GlutKeyboardCallback::keyPressedCallback(key, x, y);
            }
    };

    std::function<void(unsigned char, int, int)> GlutKeyboardCallback::keyPressedCallback = nullptr ;
    std::function<void(unsigned char, int, int)> GlutKeyboardCallback::keyUpCallback = nullptr ;

}
}
