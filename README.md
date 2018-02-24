# CPP-Socket

The following information is dedicated to how to use this API (or a C socket wrapper you would say). To start, I'd like to introduce the API's skeleton:

![tree](docs/img/tree.png)

As we can see above, I separated the API into 3 layers: IP, message and socket. In each layer, there are some sub classes that I'll explain it in detail later. Apart from the 3 main layers, there is also an extra package called "utils." That package is a helper for other packages. It helps in logging or giving error messages.

In each package, it doesn't contain only pure source codes. However, it also contains some unit testing codes. The way I organize the unit testing is very common in **"Go" (a modern programming language)** projects. I follow their style because I think it's very elegant and makes sense.

From now on, I'll be talking about how I designed, tested, and how to use the 3 main layers. I will walk you through step by step using a **top down approach**. I'll start with the IP layer. Then, I'll move to the socket layer. Lastly, I'll talk about the message layer.



## IP Layer

The IP layer is located in "inaddr". If we see what we have in the directory, we'd clearly see that we have 3 main things in the IP layer: inet_address (IP generic abstraction), ipv4, and ipv6.

* "inet_address" is an abstraction class that is designed to be very generic so that it can be extended to another protocol. It's also designed so that this class will be used to be an "interpolation" between a variety of protocols. 

* "ipv4" is the traditional IP version. This class is very specific to only support IPv4. "ipv4" supports the following:

  * Accept **dotted quad notations**
  * Accept **host names**
  * Accept **"*"**. This is a special character that means to accept incoming data to any network interface

* "ipv6" is the new version of IP, *also known as IPv6*. This class is very specific to only support IPv6. "ipv6" supports the following:

  * Accept **the 128-bit IPv6 address**
  * Accept **"*"**. This is a special character that means to accept incoming data to any network interface

  *Note: it doesn't support host names*



## Socket Layer

The socket layer is located in "socket". The same design as the IP layer. There are 3 main things in the socket layet: socket, tcp, and udp. 

* "socket" is an abstraction class that is designed to be very generic. This class is used to hold redundant codes from its subclasses and to force the abstraction of its sub classes.
* "tcp" is a wrapper class for TCP protocol
* "udp" is a wrapper class for UDP protocol



## Message Layer

In this layer, there is only one class. The purpose of this class is to be a self-growth container. The container will smartly self grow when it's necessary. When the data has been read, the container will reuse the space to be reused for another writing.



## How to use?

Following is a snippet code of how to use the API:

```c++
#include <unistd.h>
#include <iostream>
#include "ipv4.hpp"
#include "ipv6.hpp"
#include "tcp.hpp"

void server_handler(TCPSocket *socket, int client_socket_fd) {
  std::cerr << "Got a client" << std::endl;
  Message msg;

  msg.write("Hello world", 13);
  socket->send(client_socket_fd, &msg);
}

void client_handler(TCPSocket *socket, int server_socket_fd) {
  Message *msg = socket->recv();

  char buf[1024] = {0};
  while (msg->read(buf, 1024) > 0) std::cerr << buf;

  delete msg;
}

int main() {
  pid_t child_pid = fork();
  if (child_pid != 0) {
    // Parent/Server
    InetAddressV6 addr6("::", 8004);
    TCPSocket sock(addr6);
    sock.bind();
    sock.listen_and_serve(10, server_handler);
    sock.close();
  } else {
    // Child/Client
    InetAddressV4 addr4("localhost", 8004);
    TCPSocket sock(addr4);
    sock.connect();
    sock.serve(client_handler);
    sock.close();
  }

  return 0;
}
```

In this program, there is a client and a server. For the server, I used IPv6. For the client, I used IPv4. Then, the client and the server are connected through a TCP socket. Here, you can see that either client or server has to have a handler. This is, in fact, what makes the API powerful. By having a handler, you can have an ability to do a lot of things without worrying about the unnecessary details under the implementation.



## How To Run The Main Test Program?

You can simply issue the following command in the root directory of the project:

 ```sh
make test
 ```

