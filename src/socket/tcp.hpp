#ifndef TCP_HPP
#define TCP_HPP

#include "socket.hpp"

class TCPSocket : public Socket {
 public:
  TCPSocket(InetAddress &addr);
  ~TCPSocket();
  void connect();
  void bind();
  void listen_and_serve(int max_clients, void (*handler)(int client_socket_fd));
  void serve(void (*handler)(int server_socket_fd));
  // void send(DatagramMessage msg);
  // DatagramMessage recv();
};

#endif