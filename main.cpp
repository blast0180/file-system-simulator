#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "folder.hpp"
#include "file.hpp"
#include "function.hpp"

int main() {
    Folder* node = new Folder {"", nullptr, std::vector<Folder*> {}, std::vector<File> {}};

    std::cout << "tejas@FSS:" << pwd(node) << "$ ";
    std::string line;

    while (getline(std::cin, line)) {
        std::vector<std::string> parsed {parse(line)};

        if (parsed[0] == "pwd")
            std::cout << pwd(node) << '\n';
        else if (parsed[0] == "ls" && parsed[1] == "-r")
            ls_recursive(node);
        else if (parsed[0] == "ls")
            ls(node);
        else if (parsed[0] == "touch")
            touch(node, parsed[1]);
        else if (parsed[0] == "mkdir")
            mkdir(node, parsed[1]);
        else if (parsed[0] == "cd" && parsed[1] == "/")
            cd_to_root(node);
        else if (parsed[0] == "cd" && parsed[1] == "..")
            cd_to_parent(node);
        else if (parsed[0] == "cd")
            cd_to_folder(node, parsed[1]);
        else if (parsed[0] == "read")
            read(node, parsed[1]);
        else if (parsed[0] == "append")
            append(node, parsed[1], parsed);
        else if (parsed[0] == "erase")
            erase(node, parsed[1], stoi(parsed[2]), stoi(parsed[3]));
        else if (parsed[0] == "rename" && parsed[1] == "folder")
            rename_folder(node, parsed[2], parsed[3]);
        else if (parsed[0] == "rename" && parsed[1] == "file")
            rename_file(node, parsed[2], parsed[3]);
        else if (parsed[0] == "rm")
            rm(node, parsed[1]);
        else if (parsed[0] == "rmdir")
            rmdir(node, parsed[1]);
        else if (parsed[0] == "copy" && parsed[1] == "folder")
            copy_folder(node, parsed[2], parsed[3]);
        else if (parsed[0] == "move" && parsed[1] == "folder")
            move_folder(node, parsed[2], parsed[3]);
        else if (parsed[0] == "copy" && parsed[1] == "file")
            copy_file(node, parsed[2], parsed[3]);
        else if (parsed[0] == "move" && parsed[1] == "file")
            move_file(node, parsed[2], parsed[3]);

        std::cout << "tejas@FSS:" << pwd(node) << "$ ";
    }
}