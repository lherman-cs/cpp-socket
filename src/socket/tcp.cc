#include "tcp.hpp"
#include "utils.hpp"

TCPSocket::TCPSocket(InetAddress &addr) : Socket(addr, STREAM) {}

TCPSocket::~TCPSocket() {}

void TCPSocket::connect() {
  int return_val = alias_connect(this->socket_fd, this->addr->get_addr(),
                                 this->addr->get_size());
  if (return_val < 0) die(return_val, "Can't connect");
}