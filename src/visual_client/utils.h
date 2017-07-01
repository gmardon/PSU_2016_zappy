#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <vector>
#include "unistd.h"
#include "regex"

std::vector<std::string> split(const std::string& input, const std::string& regex);

#endif // UTILS_H
