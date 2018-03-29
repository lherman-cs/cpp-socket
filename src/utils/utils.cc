#include "utils/utils.hpp"

#include <cstdlib>
#include <iostream>

void die(int err_code, std::string err_msg) {
  std::cerr << "Error(" << err_code << "): " << err_msg << std::endl;
  exit(err_code);
}

void log_msg(std::string name, std::string msg) {
  std::cerr << name << ": " << msg << std::endl;
}