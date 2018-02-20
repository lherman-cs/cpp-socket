#include "message.hpp"
#include <cstdio>

int main() {
  Message msg;

  char data[9];
  int i = 0;
  for (char c = '1'; c <= '9'; c++) data[i++] = c;

  msg.write(data, sizeof(data));
  msg.write(data, sizeof(data));

  char buf[4];

  while (msg.read(buf, sizeof(buf)) > 0) {
    printf("%s\n", buf);
  }
  printf("\n");

  return 0;
}