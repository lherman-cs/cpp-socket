#include "inet_address.hpp"
#include "utils.hpp"

#include <sys/socket.h>
#include <sstream>

InetAddress::InetAddress(const struct sockaddr_in& addr4) {
  this->_addr.addr4 = addr4;
  this->size = sizeof(addr4);
}

sa_family_t InetAddress::get_family() { return this->_addr.addr.sa_family; }

struct sockaddr* InetAddress::get_addr() {
  return &this->_addr.addr;
}

int InetAddress::get_size() { return this->size; }
