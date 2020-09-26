#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

namespace my{
namespace concurrent{
    
    template<class T>
    class BlockingSafeQueue
    {
        private:
            std::queue<T> _queue;
            mutable std::mutex _mutex;
            std::condition_variable _condition;
        public:
            BlockingSafeQueue(): _queue(), _mutex(), _condition()
            {}

        void push_back(T element)
        {
            std::lock_guard<std::mutex> lock(_mutex);
            _queue.push(element);
            _condition.notify_one();
        }

        T pop_first()
        {
            std::unique_lock<std::mutex> lock(_mutex);
            _condition.wait(lock, [&] {return !_queue.empty(); });
            T val = _queue.front();
            _queue.pop();
            return val ;
        }
    };

}
}