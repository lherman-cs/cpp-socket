#ifndef TCP_HPP
#define TCP_HPP

#include "socket.hpp"

class TCPSocket : public Socket {
 public:
  TCPSocket(InetAddress &addr);
  ~TCPSocket();
  void connect();
  void bind();
  void listen_and_serve(int max_clients, void (*handler)(TCPSocket *socket,
                                                         int client_socket_fd));
  void serve(void (*handler)(TCPSocket *socket, int server_socket_fd));
  void send(int to_fd, Message *msg);
  Message *recv();
};

#endif