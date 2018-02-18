#ifndef INET_ADDRESS_HPP
#define INET_ADDRESS_HPP

#include <netinet/in.h>
#include <sys/types.h>
#include <string>

union GenericAddress {
  struct sockaddr addr;
  struct sockaddr_in addr4;
  struct sockaddr_in6 addr6;
};

class InetAddress {
 protected:
  union GenericAddress _addr;
  socklen_t size;

  InetAddress(const struct sockaddr_in& addr4);

 public:
  sa_family_t get_family();
  struct sockaddr* get_addr();
  int get_size();
};

#endif