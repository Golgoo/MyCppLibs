#include <string>
#include <cstddef> 

namespace my::util
{
    
template <class T>
std::string get_class_name()
{
    std::string str = typeid(T).name();
    int index = str.find_first_not_of("1234567890");
    if(index != std::string::npos){
        str.erase(0, index);
    }
    return str ;
}

} // namespace my::util
