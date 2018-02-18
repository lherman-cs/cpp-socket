#include <iostream>
#include "ipv4.hpp"
#include "tcp.hpp"

int main() {
  InetAddressV4 addr4("127.0.0.1", 8000);
  TCPSocket sock(addr4);
  sock.connect();

  return 0;
}