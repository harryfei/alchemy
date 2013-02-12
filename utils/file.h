#ifndef FILE_H_H_H_
#define FILE_H_H_H_

#include <string>
#include <vector>

bool is_file(const std::string &path);
std::vector<std::string> get_files(const std::string &path,const std::string &postfix);

#endif
