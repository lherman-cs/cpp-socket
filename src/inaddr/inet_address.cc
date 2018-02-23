#include "inet_address.hpp"
#include "utils.hpp"

#include <sys/socket.h>
#include <cstring>
#include <sstream>

InetAddress::InetAddress(const struct sockaddr_in& addr4) {
  this->_addr.addr4 = addr4;
  this->size = sizeof(addr4);
}

InetAddress::InetAddress(const struct sockaddr* addr, socklen_t addrlen) {
  memset(&this->_addr, 0, sizeof(this->_addr));
  memcpy(&this->_addr, addr, addrlen);
  this->size = addrlen;
}

sa_family_t InetAddress::get_family() { return this->_addr.addr.sa_family; }

struct sockaddr* InetAddress::get_addr() {
  return &this->_addr.addr;
}

socklen_t InetAddress::get_size() { return this->size; }
