#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 30

void error_handling(char *message);

int main(int argc, char *argv[]) {
    int sock;
    char message[BUF_SIZE];
    int str_len;
    struct sockaddr_in ser_adr, from_adr;

    if (argc != 1) {
        exit(1);
    }

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1)
        error_handling("socket() error");

    memset(&ser_adr, 0, sizeof(ser_adr));
    ser_adr.sin_family = AF_INET;
    ser_adr.sin_addr.s_addr = inet_addr(hostname);
    ser_adr.sin_port = htons(atoi(port number));

    // Removed connect() as it's not necessary for UDP

    while (1) {
        fputs("Input message (Q to quit): ", stdout);
        fgets(message, BUF_SIZE, stdin);

        if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
            break;

        sendto(sock, message, strlen(message), 0, (struct sockaddr *)&ser_adr, sizeof(ser_adr));

        // Use recvfrom to receive data and obtain the sender's address
        socklen_t adr_sz = sizeof(from_adr);
        str_len = recvfrom(sock, message, BUF_SIZE - 1, 0, (struct sockaddr *)&from_adr, &adr_sz);
        message[str_len] = '\0';  // Null-terminate the received message
        printf("Message from server is %s\n", message);
    }

    close(sock);
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}