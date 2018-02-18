#include "socket.hpp"
#include "utils.hpp"

#include <sys/socket.h>
#include <unistd.h>

int alias_connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
  return connect(sockfd, addr, addrlen);
}

int alias_bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
  return bind(sockfd, addr, addrlen);
}

int alias_listen(int sockfd, int backlog) { return listen(sockfd, backlog); }

int alias_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
  return accept(sockfd, addr, addrlen);
}

Socket::Socket(InetAddress &addr, Type type) {
  this->addr = &addr;
  if (type == STREAM)
    this->type = SOCK_STREAM;
  else if (type == DATAGRAM)
    this->type = SOCK_DGRAM;
  else
    die(-1, "Invalid socket type");

  this->socket_fd = socket(addr.get_family(), this->type, 0);
  if (this->socket_fd == -1) die(-1, "Socket file descriptor error");
}

Socket::~Socket() { close(this->socket_fd); }