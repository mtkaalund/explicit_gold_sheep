#ifndef ARGUMENTS_H_
#define ARGUMENTS_H_

#include <string>
#include <sstream>
#include <iostream>
#include <map>

#include <nlohmann/json.hpp>

class Arguments {
public:
    typedef enum {
        boolean,
        integer,
        string
    } argtype;

    Arguments();
    ~Arguments();
    void set_argument(std::string arg, Arguments::argtype t);
    nlohmann::json parse(int argc, char * argv[] );
private:
    nlohmann::json arg; // This will be returned as a argument config
    std::map<std::string, Arguments::argtype> cfg;
    std::map<std::string, Arguments::argtype>::iterator it;
};

#endif