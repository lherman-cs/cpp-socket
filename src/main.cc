#include <unistd.h>
#include <iostream>
#include "ipv4.hpp"
#include "tcp.hpp"

void handler(int socket_fd) {
  std::cerr << "Got a client" << std::endl;
  write(socket_fd, "Hello world\n", 12);
}

int main() {
  pid_t child_pid = fork();
  if (child_pid != 0) {
    // Parent/Server
    InetAddressV4 addr4("127.0.0.1", 8000);
    TCPSocket sock(addr4);
    sock.bind();
    sock.listen(10);
    sock.accept(handler);
  } else {
    // Child/Client
    InetAddressV4 addr4("127.0.0.1", 8000);
    TCPSocket sock(addr4);
    sock.connect();
  }

  return 0;
}