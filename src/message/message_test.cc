#include <cstdio>
#include "message.hpp"

int main() {
  Message msg;

  char data[] = "123456789";

  msg.write(data, sizeof(data));

  char buf[4];

  while (msg.read(buf, sizeof(buf)) > 0) {
    printf("%s", buf);
  }
  printf("\n");

  return 0;
}