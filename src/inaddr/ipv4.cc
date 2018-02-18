
#include "ipv4.hpp"
#include "utils.hpp"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <cstring>

InetAddressV4::InetAddressV4(std::string ip, int port) : InetAddress(IPV4) {
  this->ip = ip;
  this->port = port;

  memset(&this->addr, 0, sizeof(this->addr));
  this->addr.sin_family = InetAddress::family;

  if (ip == "*")
    this->addr.sin_addr.s_addr = htonl(INADDR_ANY);
  else {
    int return_val =
        inet_pton(InetAddress::family, ip.c_str(), &this->addr.sin_addr.s_addr);

    if (return_val <= 0) die(return_val, "Invalid IP string");
  }

  this->addr.sin_port = htons(port);
}

struct sockaddr* InetAddressV4::get_addr() {
  return (struct sockaddr*)&this->addr;
}

int InetAddressV4::get_size() { return sizeof(this->addr); }