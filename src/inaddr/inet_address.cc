#include "inet_address.hpp"
#include "utils.hpp"

#include <sys/socket.h>
#include <sstream>

InetAddress::InetAddress(Family family) {
  if (family == LOCAL)
    this->family = AF_UNIX;
  else if (family == IPV4)
    this->family = AF_INET;
  else if (family == IPV6)
    this->family = AF_INET6;
  else
    die(-1, "Invalid internet address family");
}

InetAddress::InetAddress(const InetAddress &other) {
  this->family = other.family;
}

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