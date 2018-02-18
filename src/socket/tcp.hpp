#ifndef TCP_HPP
#define TCP_HPP

#include "socket.hpp"

class TCPSocket : public Socket {
 public:
  TCPSocket(InetAddress &addr);
  ~TCPSocket();
  void connect();
  void bind();
  void listen(int max_queue_length);
  void accept(void (*handler)(int client_socket_fd));
  // void send(DatagramMessage msg);
  // DatagramMessage recv();
};

#endif