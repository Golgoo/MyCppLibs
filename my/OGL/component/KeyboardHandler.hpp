#pragma once

#include <map>
#include <vector>
#include <functional>
#include <iterator>

namespace my{
namespace OGL::component{

    class KeyboardHandler{
        private:
            std::map<unsigned char, std::function<void()>> _registered_callback ;
            std::map<unsigned char, std::function<void()>> _activated_callback ;

        public:
            KeyboardHandler()
            : _registered_callback()
            , _activated_callback()
            {}

        public:
            void keyPress(unsigned char key, int x, int y){
                try{
                    auto tmp_callback = _registered_callback.at(key);
                    _activated_callback[key] = tmp_callback ;
                }catch (const std::out_of_range& oor) {}
            }
            //TODO check if it was process once before remove it
            void keyUp(unsigned char key, int x, int y){
                _activated_callback.erase(key);
            }
            void processCallbacks(){
                for(auto pair : _activated_callback){
                    pair.second();
                }
            }
            void register_callback(unsigned char key, std::function<void()> callback){
                _registered_callback[key] = callback ;
            }
            void unregister_callback(unsigned char key){
                _registered_callback.erase(key);
            }
    };

}
}