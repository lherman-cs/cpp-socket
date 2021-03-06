#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

void die(int err_code, std::string err_msg);
void log_msg(std::string name, std::string msg);
double timestamp();

#endif