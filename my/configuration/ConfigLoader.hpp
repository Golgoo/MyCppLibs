#pragma once

#include <string>
#include <map>
#include <fstream>

namespace my{
namespace configuration{

class ConfigLoader{
    private:
        char _delim = '=';
        std::map<std::string, std::string> _parsed_map ;
        std::string _actual_config_filename ;
    public:
        ConfigLoader()
        : _parsed_map()
        {};
        void setDelimiter(char delim){_delim = delim ;};
        void load(std::string filename){
            _actual_config_filename = filename ;
            std::ifstream is(filename);
            std::string line ;
            int parseIndex ;
            int lineNumber = 0 ;

            while(std::getline(is, line)){
                parseIndex = line.find(_delim);
                if(parseIndex == std::string::npos){
                    throw std::logic_error(invalid_line_message(line, lineNumber));
                }
                lineNumber ++ ;
                _parsed_map[line.substr(0, parseIndex)] = line.substr(parseIndex + 1, line.size() - (parseIndex + 1));
            }
        };
        std::string getValue(std::string key) const {
            return _parsed_map.at(key);
        };
    private:
        std::string invalid_line_message(std::string line, int lineNumber) const
        {
            return "In : '" + _actual_config_filename + "' the line : " + std::to_string(lineNumber) + " is invalid : '" + line + "'\n" ;
        }
};

}
}
