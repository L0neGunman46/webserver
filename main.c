#include <arpa/inet.h>
#include <netinet/in.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

char *parseRoute(const char *route) {
  if (strcmp(route, "home") == 0) {
    return "static/index.html";
  } else if (strcmp(route, "about") == 0) {
    return "static/about.html";
  } else if (strcmp(route, "favicon.ico") == 0) {
    return "static/favicon.ico";
  }

  return "static/notfound.html";
}

void sendHTML(int *sock, const char *file) {
  FILE *html = fopen(file, "r");
  if (!html) {
    perror("Could not open HTML file");
    return;
  }
  // Send on our socket the file stream
  char buff[BUFFER_SIZE] = {0};
  size_t read = 0;

  // making a header

  char *header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  send(*sock, header, strlen(header), 0);

  // now send the file to display it
  //  read file into the buffer and send the buffer
  //  1024 bytes at a time
  while ((read = fread(buff, sizeof(buff[0]), BUFFER_SIZE, html)) > 0) {
    send(*sock, buff, read, 0);
  }
  fclose(html);
}

int main() {
  int serverSock;

  // TCP = SOCK_STREAM, and UDP is SOCK_DGRAM
  serverSock = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSock < 0) {
    perror("Could not get our server socket fd");
    return -1;
  }

  // variable to set up our socket server address
  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  // in addr any sets it to any address , certain network interface wil recieve
  // the connections here itis local host
  serverAddr.sin_port = htons(PORT);
  // hostmachine and network acts differently , byte order, big endian and
  // little endian, ie. ordering of bytes

  // bind socket to ports and address that was setup
  if (bind(serverSock, (struct sockaddr *)&serverAddr, sizeof serverAddr) < 0) {
    perror("Could not bind to server socket and address ");
    return -1;
  }

  // telling server to listen
  if (listen(serverSock, 5) < 0) {
    perror("Could not listen on server sockt ip");
    return -1;
  }

  printf("Listening on port %d\n", PORT);

  // wait of a connection
  while (1) {
    // client info
    struct sockaddr_in clientAddr;
    socklen_t clientLen = sizeof clientAddr;
    int *clientSocket = malloc(sizeof(int));

    // client addr info is ready accept the connection
    if ((*clientSocket = accept(serverSock, (struct sockaddr *)&clientAddr,
                                &clientLen)) < 0) {
      perror("Could not accept client");
      continue;
    }

    printf("Client connected\n");
    char recBuf[BUFFER_SIZE] = {0};
    recv(*clientSocket, recBuf, BUFFER_SIZE, 0);
    // printf("%s\n", recBuf);
    char *token = recBuf + 5;
    char *route = strtok(token, " ");
    sendHTML(clientSocket, parseRoute(route));

    close(*clientSocket);
    printf("Client Disconnected\n");

    free(clientSocket);
  }
  close(serverSock);
  return 0;
}
