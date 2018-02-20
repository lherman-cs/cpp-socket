#include <unistd.h>
#include <iostream>
#include "ipv4.hpp"
#include "tcp.hpp"

void server_handler(Socket *socket, int client_socket_fd) {
  std::cerr << "Got a client" << std::endl;
  write(client_socket_fd, "Hello world\n", 12);
}

void client_handler(Socket *socket, int server_socket_fd) {
  Message *msg = socket->recv();

  char buf[4];
  while (msg->read(buf, 4) > 0) std::cerr << buf;

  delete msg;
}

int main() {
  pid_t child_pid = fork();
  if (child_pid != 0) {
    // Parent/Server
    InetAddressV4 addr4("127.0.0.1", 8002);
    TCPSocket sock(addr4);
    sock.bind();
    sock.listen_and_serve(10, server_handler);
  } else {
    // Child/Client
    InetAddressV4 addr4("127.0.0.1", 8002);
    TCPSocket sock(addr4);
    sock.connect();
    sock.serve(client_handler);
    sock.close();
  }

  return 0;
}