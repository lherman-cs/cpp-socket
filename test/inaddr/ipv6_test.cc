#include "ipv6.hpp"
#include <iostream>

int main() {
  InetAddressV6 ipv61("*", 8000);
  InetAddressV6 ipv62("::1", 8000);
  InetAddressV6 ipv63("::", 8000);

  return 0;
}