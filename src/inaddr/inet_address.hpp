#ifndef INET_ADDRESS_HPP
#define INET_ADDRESS_HPP

#include <netinet/in.h>
#include <string>

enum Family { LOCAL, IPV4, IPV6 };

class InetAddress {
 protected:
  int family;
  std::string ip;
  int port;
  struct sockaddr* generic_addr;
  int size;

  InetAddress(Family family, std::string ip, int port,
              struct sockaddr* generic_addr, int size);

 public:
  InetAddress(const InetAddress& other);
  struct sockaddr* get_generic_addr();
  int get_size();
  std::string info();
  int get_family();
};

#endif