#ifndef TCP_HPP
#define TCP_HPP

#include "socket.hpp"

class TCPSocket : public Socket {
 public:
  TCPSocket(InetAddress &addr);
  ~TCPSocket();
  void connect();
  // void send(DatagramMessage msg);
  // DatagramMessage recv();
};

#endif