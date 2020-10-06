#pragma once

#include <memory>
#include <map>
#include <functional>

#include <my/pattern/factory.hpp>
#include <my/pattern/util.hpp>

#include <stdexcept>
#include <string>

namespace my::pattern
{

template <class T>
class Builder{
    private:
        std::shared_ptr<T> _instance ;
        my::pattern::Factory<T> * _instance_factory ;

        std::map<int, std::function<void(T&)>> _operations ;
    public:
        Builder(my::pattern::Factory<T>* instance_factory)
        : _instance(std::move(instance_factory->create()))
        , _instance_factory(instance_factory)
        , _operations()
        {}
    private:
        inline void reset(){
            _instance = std::shared_ptr<T>(_instance_factory->create());
        }
    
    private:
        virtual void init_operations() = 0 ;

    public:
        /**
         * @brief The build of the current instance is finished and returned.
         * 
         * A new instance is created with the current factory to be built
         * 
         * @return The current instance
         */
        std::shared_ptr<T> buildIt(){ 
            auto instance = _instance ;
            reset();
            return instance ;
        }

        inline void processOperation(int operation_number){
            auto fct = _operations.find(operation_number);
            if(fct == _operations.end()){
                std::string error_msg = "The builder of '" ;
                error_msg.append(my::util::get_class_name<T>());
                error_msg.append("' don't know the operation number : ");
                error_msg.append(std::to_string(operation_number));
                throw std::runtime_error(error_msg.c_str());
            }
            fct->second(*_instance);
        }
    
        inline void registerBuildingOperation(int operation_number, std::function<void(T&)> fct){
            _operations[operation_number] = fct ;
        }

        inline void setFactory(my::pattern::Factory<T>* instance_factory){
            _instance_factory = instance_factory ;
        }
};

} // namespace my::pattern
