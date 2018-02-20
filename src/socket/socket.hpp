#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <sys/socket.h>
#include "inet_address.hpp"
#include "message.hpp"

int alias_close(int fd);
int alias_connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int alias_bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int alias_listen(int sockfd, int backlog);
int alias_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

class Socket {
 protected:
  InetAddress *addr;
  int type;
  int socket_fd;
  Socket(InetAddress &addr, int type);
  ~Socket();

 public:
  void close();
  virtual void connect() = 0;
  virtual void bind() = 0;
  virtual void listen_and_serve(int max_clients,
                                void (*handler)(Socket *socket,
                                                int client_socket_fd)) = 0;
  virtual void serve(void (*handler)(Socket *socket, int server_socket_fd)) = 0;
  virtual void send(Message *msg) = 0;
  virtual Message *recv() = 0;
};

#endif