#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <sys/socket.h>
#include "inet_address.hpp"

enum Type { STREAM, DATAGRAM };
int alias_connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int alias_bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int alias_listen(int sockfd, int backlog);
int alias_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

class Socket {
 protected:
  InetAddress *addr;
  int type;
  int socket_fd;
  Socket(InetAddress &addr, Type type);
  ~Socket();

 public:
  virtual void connect() = 0;
  virtual void bind() = 0;
  virtual void listen(int max_queue_length) = 0;
  virtual void accept(void (*handler)(int client_socket_fd)) = 0;
  // virtual void send(DatagramMessage msg) = 0;
  // virtual DatagramMessage recv() = 0;
};

#endif