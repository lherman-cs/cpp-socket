#include <netinet/in.h>
#include <netinet/udp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t child_pid = fork();

  if (child_pid != 0) {
    // Parent / Server
    int udp_fd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = 8000;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(udp_fd, (struct sockaddr *)&addr, sizeof(addr));

    for (;;) {
      char buf[1024] = {0};
      struct sockaddr_storage client_addr;
      socklen_t client_addr_len = sizeof(client_addr);
      ssize_t recv_len =
          recvfrom(udp_fd, buf, sizeof(buf), 0, (struct sockaddr *)&client_addr,
                   &client_addr_len);

      fprintf(stderr, "server: received %s\n", buf);

      char data[1024] = "Hello world. How are you doing?";
      ssize_t send_len =
          sendto(udp_fd, data, sizeof(data), 0, (struct sockaddr *)&client_addr,
                 client_addr_len);
    }

  } else {
    // child / client
    int udp_fd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = 8000;
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    char data[1024] = "My name is Lukas";
    struct sockaddr_storage server_addr;
    socklen_t server_addr_len = sizeof(server_addr);

    char *to_send = data;
    ssize_t need = sizeof(data);
    ssize_t send_len;

    while ((send_len = sendto(udp_fd, to_send, need, 0,
                              (struct sockaddr *)&addr, sizeof(addr))) > 0) {
      fprintf(stderr, "server: sent %d\n", (int)send_len);
      need -= send_len;
      to_send += send_len;
    }

    char buf[4] = {0};
    ssize_t recv_len;
    while ((recv_len = recvfrom(udp_fd, buf, sizeof(buf) - 1, 0,
                                (struct sockaddr *)&server_addr,
                                &server_addr_len)) > 0) {
      fprintf(stderr, "client: %s\n", buf);
      fprintf(stderr, "Reading\n");
    }
    fprintf(stderr, "Done\n");
  }
  return 0;
}