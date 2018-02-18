#include "utils.hpp"

#include <cstdlib>
#include <iostream>

void die(int err_code, std::string err_msg) {
  std::cerr << "Error(" << err_code << "): " << err_msg << std::endl;
  exit(err_code);
}