#ifndef INET_ADDRESS_HPP
#define INET_ADDRESS_HPP

#include <netinet/in.h>
#include <string>

enum Family { LOCAL, IPV4, IPV6 };

class InetAddress {
 protected:
  int family;
  InetAddress(Family family);

 public:
  InetAddress(const InetAddress& other);
  virtual struct sockaddr* get_addr() = 0;
  virtual int get_size() = 0;
  std::string info();
  int get_family();
};

#endif