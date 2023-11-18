#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h> 

#define BUF_SIZE 10


void error_handling(char *message);



int main(int argc, char *argv[]) {
    int ser_sock;
    char message[BUF_SIZE];
    int str_len;
    struct sockaddr_in ser_adr, clnt_adr; 
    socklen_t clnt_adr_sz;

   

    ser_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (ser_sock == -1)
        error_handling("UDP socket creation error");

    memset(&ser_adr, 0, sizeof(ser_adr));
    ser_adr.sin_family = AF_INET;
   if (inet_pton(AF_INET, "hostname", &ser_adr.sin_addr) <= 0)
    error_handling("inet_pton() error");
    ser_adr.sin_port = htons(atoi("port no"));

    if (bind(ser_sock, (struct sockaddr *)&ser_adr, sizeof(ser_adr)) == -1)
        error_handling("bind() error");

    while (1) {
        clnt_adr_sz = sizeof(clnt_adr);
        str_len = recvfrom(ser_sock, message, BUF_SIZE, 0, (struct sockaddr *)&clnt_adr, &clnt_adr_sz);
        sendto(ser_sock, message, str_len, 0, (struct sockaddr *)&clnt_adr, clnt_adr_sz);
    }

 

    close(ser_sock);
    return 0;
}


void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
