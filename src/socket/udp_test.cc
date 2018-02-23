#include "udp.hpp"
#include <unistd.h>
#include <iostream>
#include "ipv4.hpp"
#include "utils.hpp"

void server_handler(UDPSocket *socket, InetAddress client_addr) {
  Message msg;

  msg.write("Hello world", 13);
  socket->send(&client_addr, &msg);
}

void client_handler(UDPSocket *socket, InetAddress server_addr) {
  Message tmp(2);

  socket->send(&server_addr, &tmp);

  Message *msg = socket->recv();

  char buf[1024] = {0};
  while (msg->read(buf, 1024) > 0) log_msg("client", buf);

  delete msg;
}

int main() {
  pid_t child_pid = fork();
  if (child_pid != 0) {
    // Parent/Server
    InetAddressV4 addr4("localhost", 8004);
    UDPSocket sock(addr4);
    sock.bind();
    sock.listen_and_serve(server_handler);
  } else {
    // Child/Client
    InetAddressV4 addr4("localhost", 8004);
    UDPSocket sock(addr4);
    sock.serve(client_handler);
  }

  return 0;
}