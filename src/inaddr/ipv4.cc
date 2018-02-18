
#include "ipv4.hpp"
#include "utils.hpp"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <cstring>

struct sockaddr_in InetAddressV4::construct_addr(std::string ip,
                                                 uint16_t port) {
  struct sockaddr_in addr;

  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;

  if (ip == "*")
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
  else {
    int return_val = inet_pton(AF_INET, ip.c_str(), &addr.sin_addr.s_addr);
    if (return_val <= 0) die(return_val, "Invalid IP string");
  }
  addr.sin_port = htons(port);

  return addr;
}

InetAddressV4::InetAddressV4(std::string ip, uint16_t port)
    : InetAddress(construct_addr(ip, port)) {}
