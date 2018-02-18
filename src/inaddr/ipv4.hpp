#ifndef IPV4_HPP
#define IPV4_HPP

#include <netinet/in.h>
#include <string>
#include "inet_address.hpp"

class InetAddressV4 : public InetAddress {
 private:
  struct sockaddr_in addr;
  std::string ip;
  int port;

 public:
  // If "ip" = "*", use any ip address from the network interface
  InetAddressV4(std::string ip, int port);
  struct sockaddr* get_addr();
  int get_size();
};

#endif