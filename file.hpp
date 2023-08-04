#ifndef _FILE_HPP
#define _FILE_HPP

#include <string>

struct File {
    std::string name;
    std::string content;

    File(std::string& name)
        : name(name), content("") {}
};

#endif