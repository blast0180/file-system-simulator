#ifndef _FOLDER_HPP
#define _FOLDER_HPP

#include <string>
#include <vector>
#include "file.hpp"

struct Folder {
    std::string name;

    Folder* parent;

    std::vector<Folder*> folder;
    std::vector<File> file;

    Folder(std::string name, Folder* parent, std::vector<Folder*> folder, std::vector<File> file)
        : name(name), parent(parent), folder(folder), file(file) {}
    
    Folder(Folder& other)
        : name(other.name), parent(other.parent), folder(), file() {
        
        for (Folder*& sub_folder : other.folder) {
            Folder* new_folder = new Folder(*sub_folder);
            folder.push_back(new_folder);
        }
        for (File& sub_file : other.file) {
            file.push_back(sub_file);
        }
    }
};

#endif