#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "main_imports.hpp"
#include <filesystem>

bool yes_or_no(string text); //ask the yes/no question
string read_from_file(string filename); //reads the specified file
vector<string> list_dir(string path); //lists the specified directory

#endif