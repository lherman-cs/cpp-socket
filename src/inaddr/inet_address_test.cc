#include "inet_address.hpp"
#include <assert.h>
#include <cstdio>
#include <iostream>
#include "ipv4.hpp"

int main() {
  InetAddressV4 ipv4("127.0.0.1", 8000);
  struct sockaddr* addr = ipv4.get_addr();
  socklen_t size1 = ipv4.get_size();

  InetAddress ip2(addr, size1);

  struct sockaddr_in* addr1 = (struct sockaddr_in*)addr;
  struct sockaddr_in* addr2 = (struct sockaddr_in*)ip2.get_addr();
  socklen_t size2 = ip2.get_size();

  assert(addr1->sin_family == addr2->sin_family);
  assert(addr1->sin_port == addr2->sin_port);
  assert(addr1->sin_addr.s_addr == addr2->sin_addr.s_addr);

  // Test copy constructor
  InetAddress copy(ip2);
  assert(copy.get_size() == ip2.get_size());
  assert(((struct sockaddr_in*)copy.get_addr())->sin_family ==
         ((struct sockaddr_in*)ip2.get_addr())->sin_family);
  assert(((struct sockaddr_in*)copy.get_addr())->sin_port ==
         ((struct sockaddr_in*)ip2.get_addr())->sin_port);
  assert(((struct sockaddr_in*)copy.get_addr())->sin_addr.s_addr ==
         ((struct sockaddr_in*)ip2.get_addr())->sin_addr.s_addr);

  return 0;
}