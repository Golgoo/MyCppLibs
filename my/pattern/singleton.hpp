#pragma once

#include <my/pattern/factory.hpp>

#include <memory>

namespace my::pattern
{

template <class T>
class Singleton{
    public:
        Singleton(my::pattern::Factory<T> &singletonCreationFactory)
        : _instance(std::move(singletonCreationFactory.create()))
        {}

    private:
        std::shared_ptr<T> _instance ;

    public:
        std::shared_ptr<T> getInstance(){
            return _instance ;
        }
};

}