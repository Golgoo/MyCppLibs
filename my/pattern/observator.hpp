#pragma once

#include <set>
#include <algorithm>

namespace my::pattern{

    template<class T>
    class Observer{
        public:
            virtual void handle(T &observable) = 0 ;
    };

    template<class T>
    class Observable{

        private:
            std::set<Observer<T>*> _observers ;

        public:
            void addObserver(Observer<T> *observer){
                _observers.insert(observer);
            }
        protected:
            void notify(T &obervable){
                std::for_each(_observers.begin(), _observers.end(), [&obervable](Observer<T>* observer){
                    try{
                        observer->handle(obervable);
                    }catch(...){}
                });
            }
    };
}