#include "inet_address.hpp"
#include "utils.hpp"

#include <sys/socket.h>
#include <sstream>

InetAddress::InetAddress(Family family, std::string ip, int port,
                         struct sockaddr* generic_addr, int size) {
  if (family == LOCAL)
    this->family = AF_UNIX;
  else if (family == IPV4)
    this->family = AF_INET;
  else if (family == IPV6)
    this->family = AF_INET6;
  else
    die(-1, "Invalid internet address family");

  this->ip = ip;
  this->port = port;
  this->generic_addr = generic_addr;
  this->size = size;
}

InetAddress::InetAddress(const InetAddress& other) {
  this->family = other.family;
  this->ip = other.ip;
  this->port = other.port;
  this->generic_addr = other.generic_addr;
  this->size = other.size;
}

struct sockaddr* InetAddress::get_generic_addr() {
  return this->generic_addr;
}

int InetAddress::get_size() { return this->size; }

std::string InetAddress::info() {
  std::ostringstream sout;

  std::string family;
  switch (this->family) {
    case AF_UNIX:
      family = "AF_UNIX";
      break;
    case AF_INET:
      family = "AF_INET";
      break;
    case AF_INET6:
      family = "AF_INET6";
      break;
  }

  sout << "   Family: " << family << "\n";
  return sout.str();
}

int InetAddress::get_family() { return this->family; }