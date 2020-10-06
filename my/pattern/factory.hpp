#pragma once

#include <memory>

namespace my::pattern{

template <class T>
class Factory{
    public:
        virtual T * create() = 0;
};
}