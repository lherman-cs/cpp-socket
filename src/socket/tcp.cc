#include "tcp.hpp"
#include "utils.hpp"

#include <unistd.h>

TCPSocket::TCPSocket(InetAddress &addr) : Socket(addr, STREAM) {}

TCPSocket::~TCPSocket() {}

void TCPSocket::connect() {
  int return_val = alias_connect(
      this->socket_fd, this->addr->get_generic_addr(), this->addr->get_size());
  if (return_val < 0) die(return_val, "Can't connect");
}

void TCPSocket::bind() {
  int return_val = alias_bind(this->socket_fd, this->addr->get_generic_addr(),
                              this->addr->get_size());

  if (return_val < 0) die(return_val, "Can't bind");
}

void TCPSocket::listen(int max_queue_length) {
  int return_val = alias_listen(this->socket_fd, max_queue_length);

  if (return_val < 0) die(return_val, "Can't listen");
}

void TCPSocket::accept(void (*handler)(int client_socket_fd)) {
  for (;;) {
    struct sockaddr_storage client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    int client_socket_fd = alias_accept(
        this->socket_fd, (struct sockaddr *)&client_addr, &client_addr_len);

    if (client_socket_fd == -1)
      die(-1, "Invalid client socket file descriptor");
    handler(client_socket_fd);
    close(client_socket_fd);
  }
}