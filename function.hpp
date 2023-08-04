#ifndef _FUNCTION_HPP
#define _FUNCTION_HPP

#include <string>
#include "folder.hpp"

std::vector<std::string> parse(std::string&);
std::string pwd(Folder*&);
void ls_recursive(Folder*&);
void ls(Folder*&);
void touch(Folder*&, std::string&);
void mkdir(Folder*&, std::string&);
void cd_to_root(Folder*&);
void cd_to_parent(Folder*&);
int cd_to_folder(Folder*&, std::string&);
void read(Folder*&, std::string&);
void append(Folder*&, std::string&, std::vector<std::string>&);
void erase(Folder*&, std::string&, int, int);
void rename_folder(Folder*&, std::string&, std::string&);
void rename_file(Folder*&, std::string&, std::string&);
void rm(Folder*&, std::string&);
void rmdir(Folder*&, std::string&);
void copy_folder(Folder*&, std::string&, std::string&);
void move_folder(Folder*&, std::string&, std::string&);
void copy_file(Folder*&, std::string&, std::string&);
void move_file(Folder*&, std::string&, std::string&);

#endif