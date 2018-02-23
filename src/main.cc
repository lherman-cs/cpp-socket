#include <unistd.h>
#include <iostream>
#include "ipv4.hpp"
#include "ipv6.hpp"
#include "tcp.hpp"

void server_handler(TCPSocket *socket, int client_socket_fd) {
  std::cerr << "Got a client" << std::endl;
  Message msg;

  msg.write("Hello world", 13);
  socket->send(client_socket_fd, &msg);
}

void client_handler(TCPSocket *socket, int server_socket_fd) {
  Message *msg = socket->recv();

  char buf[1024] = {0};
  while (msg->read(buf, 1024) > 0) std::cerr << buf;

  delete msg;
}

int main() {
  pid_t child_pid = fork();
  if (child_pid != 0) {
    // Parent/Server
    InetAddressV6 addr6("::", 8004);
    TCPSocket sock(addr6);
    sock.bind();
    sock.listen_and_serve(10, server_handler);
  } else {
    // Child/Client
    InetAddressV4 addr4("localhost", 8004);
    TCPSocket sock(addr4);
    sock.connect();
    sock.serve(client_handler);
    sock.close();
  }

  return 0;
}