#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include "inaddr/ipv4.hpp"
#include "socket/tcp.hpp"
#include "utils/utils.hpp"
#define min(a, b) a < b ? a : b

int CHUNK_SIZE;

void handler(TCPSocket *socket, int server_socket_fd) {
  double start, total_time, throughput;
  int total_size = 0, size;
  char *dummy = (char *)malloc(CHUNK_SIZE);

  start = timestamp();
  for (;;) {
    switch (size = recv(server_socket_fd, dummy, CHUNK_SIZE, 0)) {
      case -1:  // An error occured
      case 0:   // Finished
        goto stop;
        break;
      default:
        total_size += size;
        break;
    }
  }
stop:
  total_time = timestamp() - start;

  // If size == 0, that means there's no error during transferring
  if (size == 0) {
    // Calculate throughput in Mbps
    throughput = ((double)8 * total_size) / (total_time * 1000000);
    printf("transfer_size: %d chunk_size: %d throughput: %.4f Mbps\n",
           total_size, CHUNK_SIZE, throughput);
  }

  free(dummy);
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    printf("Usage: ./client [server_ip] [port] [chunk_size]\n");
    exit(1);
  }
  int port = atoi(argv[2]);
  CHUNK_SIZE = atoi(argv[3]);

  InetAddressV4 ipv4(argv[1], port);
  TCPSocket socket(ipv4);
  socket.connect();
  socket.serve(handler);
  socket.close();

  return 0;
}