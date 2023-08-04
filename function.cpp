#include <iostream>
#include <algorithm>
#include <sstream>
#include "function.hpp"
#include "folder.hpp"

// TODO - Add support for parsing "string".
std::vector<std::string> parse(std::string& line) {
    std::vector<std::string> parsed;
    std::istringstream iss(line);
    std::string str;

    while (iss >> str)
        parsed.push_back(str);

    return parsed;
}

std::string pwd(Folder*& folder) {
    if (folder == nullptr)
        return std::string {};

    return pwd(folder->parent).append(folder->name).append("/");
}

void ls_recursive_helper(Folder*& node, std::string& spacing) {
    if (node->file.empty() && node->folder.empty())
        return;

    for (Folder*& _folder : node->folder) {
        std::cout << spacing << _folder->name << '\n';
        spacing.append(4, ' ');
        ls_recursive_helper(_folder, spacing);
        spacing.erase(spacing.end() - 4, spacing.end());
    }
    for (File& _file : node->file)
        std::cout << spacing << _file.name << '\n';
}

void ls_recursive(Folder*& node) {
    std::string spacing {};
    ls_recursive_helper(node, spacing);
}

void ls(Folder*& node) {
    if (node->file.empty() && node->folder.empty())
        return;

    for (Folder*& _folder : node->folder)
        std::cout << _folder->name << '\n';

    for (File& _file : node->file)
        std::cout << _file.name << '\n';
}

void touch(Folder*& node, std::string& file_name) {
    if (std::any_of(node->file.begin(), node->file.end(), [&file_name](File& file) -> bool {
        return file_name == file.name;
    })) {
        std::cout << "File '" << file_name << "' already exists.\n";
        return;
    }
    node->file.push_back(File {file_name});
}

void mkdir(Folder*& node, std::string& folder_name) {
    if (std::any_of(node->folder.begin(), node->folder.end(), [&folder_name](Folder*& folder) -> bool {
        return folder_name == folder->name;
    })) {
        std::cout << "Folder '" << folder_name << "' already exists.\n";
        return;
    }
    node->folder.push_back(new Folder {folder_name, node, std::vector<Folder*> {}, std::vector<File> {}});
}

void cd_to_root(Folder*& node) {
    while (node->parent != nullptr)
        cd_to_parent(node);
}

void cd_to_parent(Folder*& node) {
    if (node->parent == nullptr)
        return;
    node = node->parent;
}

int cd_to_folder(Folder*& node, std::string& folder_name) {
    if (std::vector<Folder*>::iterator it {std::find_if(node->folder.begin(), node->folder.end(), [&folder_name](Folder*& folder) -> bool {
        return folder_name == folder->name;
    })}; it != node->folder.end()) {
        node = *it;
        return 0;
    }
    std::cout << "Folder '" << folder_name << "' does not exist.\n";
    return -1;
}

void read(Folder*& node, std::string& file_name) {
    if (std::vector<File>::iterator it {std::find_if(node->file.begin(), node->file.end(), [&file_name](File& file) -> bool {
        return file_name == file.name;
    })}; it != node->file.end()) {
        std::cout << it->content;
        if (!it->content.empty())
            std::cout << '\n';
        return;
    }
    std::cout << "File '" << file_name << "' does not exist.\n";
}

void append(Folder*& node, std::string& file_name, std::vector<std::string>& parsed) {
    if (std::vector<File>::iterator it {std::find_if(node->file.begin(), node->file.end(), [&file_name](File& file) -> bool {
        return file_name == file.name;
    })}; it != node->file.end()) {
        for (int i {2}; i < parsed.size(); ++i)
            it->content.append(parsed[i] + " ");
        return;
    }
    std::cout << "File '" << file_name << "' does not exist.\n";
}

void erase(Folder*& node, std::string& file_name, int index, int count) {
    if (std::vector<File>::iterator it {std::find_if(node->file.begin(), node->file.end(), [&file_name](File& file) -> bool {
        return file_name == file.name;
    })}; it != node->file.end()) {
        it->content.erase(index, count);
        return;
    }
    std::cout << "File '" << file_name << "' does not exist.\n";
}

void rename_folder(Folder*& node, std::string& from_name, std::string& to_name) {
    if (std::vector<Folder*>::iterator it_folder {std::find_if(node->folder.begin(), node->folder.end(), [&from_name](Folder*& folder) -> bool {
        return from_name == folder->name;
    })}; it_folder != node->folder.end()) {
        (*it_folder)->name = to_name;
        return;
    }
    std::cout << "Folder '" << from_name << "' does not exist.\n";
}

void rename_file(Folder*& node, std::string& from_name, std::string& to_name) {
    if (std::vector<File>::iterator it_file {std::find_if(node->file.begin(), node->file.end(), [&from_name](File& file) -> bool {
        return from_name == file.name;
    })}; it_file != node->file.end()) {
        it_file->name = to_name;
        return;
    }
    std::cout << "File '" << from_name << "' does not exist.\n";
}

void rm(Folder*& node, std::string& name) {
    if (std::vector<File>::iterator it {std::find_if(node->file.begin(), node->file.end(), [&name](File& file) -> bool {
        return name == file.name;
    })}; it != node->file.end()) {
        node->file.erase(it);
        return;
    }
    std::cout << "File '" << name << "' does not exist.\n";
}

void rmdir(Folder*& node, std::string& name) {
    if (std::vector<Folder*>::iterator it {std::find_if(node->folder.begin(), node->folder.end(), [&name](Folder*& folder) -> bool {
        return name == folder->name;
    })}; it != node->folder.end()) {
        delete *it;
        node->folder.erase(it);
        return;
    }
    std::cout << "Folder '" << name << "' does not exist.\n";
}

// TODO - Add support for going back in path using '..'.
std::vector<std::string> path_parse(std::string line) {
    std::vector<std::string> parsed;

    for (int i {1}; i < line.size() - 1; ++i) {
        if (line[i] == '/')
            continue;

        if (line[i - 1] == '/')
            parsed.push_back(std::string(1, line[i]));
        else
            parsed.back().push_back(line[i]);
    }
    return parsed;
}

void copy_folder(Folder*& node, std::string& folder_name, std::string& path) {
    std::vector<Folder*>::iterator it {std::find_if(node->folder.begin(), node->folder.end(), [&folder_name](Folder*& folder) -> bool {
        return folder_name == folder->name;
    })};
    if (it == node->folder.end()) {
        std::cout << "Folder '" << folder_name << "' does not exist.\n";
        return;
    }
    Folder* temp_node = node;
    cd_to_root(temp_node);
    std::vector<std::string> parsed {path_parse(path)};

    for (std::string& folder_name : parsed)
        if (cd_to_folder(temp_node, folder_name) == -1)
            return;

    if (std::vector<Folder*>::iterator it {std::find_if(temp_node->folder.begin(), temp_node->folder.end(), [&folder_name](Folder*& folder) -> bool {
        return folder_name == folder->name;
    })}; it != temp_node->folder.end()) {
        std::cout << "Folder with the name '" << folder_name << "' already exists.\n";
        return;
    }
    Folder* temp = new Folder(**it);
    temp->parent = *it;
    temp_node->folder.push_back(temp);
}

void move_folder(Folder*& node, std::string& folder_name, std::string& path) {
    std::vector<Folder*>::iterator it {std::find_if(node->folder.begin(), node->folder.end(), [&folder_name](Folder*& folder) -> bool {
        return folder_name == folder->name;
    })};
    if (it == node->folder.end()) {
        std::cout << "Folder '" << folder_name << "' does not exist.\n";
        return;
    }
    Folder* temp_node = node;
    cd_to_root(temp_node);
    std::vector<std::string> parsed {path_parse(path)};

    for (std::string& folder_name : parsed)
        if (cd_to_folder(temp_node, folder_name) == -1)
            return;

    if (std::vector<Folder*>::iterator it {std::find_if(temp_node->folder.begin(), temp_node->folder.end(), [&folder_name](Folder*& folder) -> bool {
        return folder_name == folder->name;
    })}; it != temp_node->folder.end()) {
        std::cout << "Folder with the name '" << folder_name << "' already exists.\n";
        return;
    }
    Folder* temp = new Folder(**it);

    if (temp_node == *it) {
        std::cout << "Cannot move: The destination folder is a subfolder of the source folder.\n";
        return;
    }
    temp->parent = *it;
    temp_node->folder.push_back(temp);
    node->folder.erase(it);
}

void copy_file(Folder*& node, std::string& file_name, std::string& path) {
    std::vector<File>::iterator it {std::find_if(node->file.begin(), node->file.end(), [&file_name](File& file) -> bool {
        return file_name == file.name;
    })};
    if (it == node->file.end()) {
        std::cout << "File '" << file_name << "' does not exist.\n";
        return;
    }
    Folder* temp_node = node;
    cd_to_root(temp_node);
    std::vector<std::string> parsed {path_parse(path)};

    for (std::string& folder_name : parsed)
        if (cd_to_folder(temp_node, folder_name) == -1)
            return;

    if (std::vector<File>::iterator it {std::find_if(temp_node->file.begin(), temp_node->file.end(), [&file_name](File& file) -> bool {
        return file_name == file.name;
    })}; it != temp_node->file.end()) {
        std::cout << "File with the name '" << file_name << "' already exists.\n";
        return;
    }

    temp_node->file.push_back(*it);
}

void move_file(Folder*& node, std::string& file_name, std::string& path) {
    std::vector<File>::iterator it {std::find_if(node->file.begin(), node->file.end(), [&file_name](File& file) -> bool {
        return file_name == file.name;
    })};
    if (it == node->file.end()) {
        std::cout << "File '" << file_name << "' does not exist.\n";
        return;
    }
    Folder* temp_node = node;
    cd_to_root(temp_node);
    std::vector<std::string> parsed {path_parse(path)};

    for (std::string& folder_name : parsed)
        if (cd_to_folder(temp_node, folder_name) == -1)
            return;

    if (std::vector<File>::iterator it {std::find_if(temp_node->file.begin(), temp_node->file.end(), [&file_name](File& file) -> bool {
        return file_name == file.name;
    })}; it != temp_node->file.end()) {
        std::cout << "File with the name '" << file_name << "' already exists.\n";
        return;
    }
    temp_node->file.push_back(*it);
    node->file.erase(it);
}