#include "tcp.hpp"
#include "utils.hpp"

#include <unistd.h>

TCPSocket::TCPSocket(InetAddress &addr) : Socket(addr, SOCK_STREAM) {}

TCPSocket::~TCPSocket() {}

void TCPSocket::connect() {
  int return_val = alias_connect(this->socket_fd, this->addr.get_addr(),
                                 this->addr.get_size());
  if (return_val < 0) die(return_val, "Can't connect");
}

void TCPSocket::listen_and_serve(int max_clients,
                                 void (*handler)(TCPSocket *socket,
                                                 int client_socket_fd)) {
  int return_val = alias_listen(this->socket_fd, max_clients);
  if (return_val < 0) die(return_val, "Can't listen");

  for (;;) {
    struct sockaddr_storage client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    int client_socket_fd = alias_accept(
        this->socket_fd, (struct sockaddr *)&client_addr, &client_addr_len);

    if (client_socket_fd == -1)
      die(-1, "Invalid client socket file descriptor");
    handler(this, client_socket_fd);
    alias_close(client_socket_fd);
  }
}

void TCPSocket::serve(void (*handler)(TCPSocket *socket,
                                      int server_socket_fd)) {
  handler(this, this->socket_fd);
}

void TCPSocket::send(int to_fd, Message *msg) {
  char buf[1024] = {0};
  ssize_t len;

  while ((len = msg->read(buf, sizeof(buf))) > 0)
    alias_send(to_fd, buf, len, 0);
}

Message *TCPSocket::recv() {
  char buf[1024] = {0};
  ssize_t len;
  Message *msg = new Message();

  while ((len = alias_recv(this->socket_fd, buf, sizeof(buf), 0)) > 0)
    msg->write(buf, len);

  return msg;
}