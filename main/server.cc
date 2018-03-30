#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include "inaddr/ipv4.hpp"
#include "socket/tcp.hpp"
#include "utils/utils.hpp"
#define IP "*"
#define MAX_CLIENTS 1000
#define min(a, b) a < b ? a : b

int TRANSFER_SIZE;
int CHUNK_SIZE;

void handler(TCPSocket *socket, int client_socket_fd) {
  int transfer_size = TRANSFER_SIZE, size, to_be_sent;
  char *dummy = (char *)malloc(CHUNK_SIZE);

  for (;;) {
    to_be_sent = min(transfer_size, CHUNK_SIZE);
    size = send(client_socket_fd, (void *)dummy, to_be_sent, 0);

    switch (size) {
      case -1:  // An error occured
      case 0:
        goto stop;  // Transfer finished
        break;
      default:
        transfer_size -= size;
        break;
    }
  }
stop:

  free(dummy);
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    printf("Usage: ./server [port] [transfer_size] [chunk_size]\n");
    exit(1);
  }

  // Set high priority
  nice(0);

  int port = atoi(argv[1]);
  TRANSFER_SIZE = atoi(argv[2]);
  CHUNK_SIZE = atoi(argv[3]);

  InetAddressV4 ipv4(IP, port);
  TCPSocket socket(ipv4);
  socket.bind();
  socket.listen_and_serve(MAX_CLIENTS, handler);
  socket.close();

  return 0;
}