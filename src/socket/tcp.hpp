#ifndef TCP_HPP
#define TCP_HPP

#include "socket.hpp"

class TCPSocket : public Socket {
 public:
  TCPSocket(InetAddress &addr);
  ~TCPSocket();
  void connect();
  void bind();
  void listen_and_serve(int max_clients,
                        void (*handler)(Socket *socket, int client_socket_fd));
  void serve(void (*handler)(Socket *socket, int server_socket_fd));
  void send(Message *msg);
  Message *recv();
};

#endif