#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

ssize_t s_send (int fd, char* buffer, size_t len) {
    ssize_t sent = 0;
    while (sent < len) {
        ssize_t current = send(fd, buffer +sent,len-sent, MSG_NOSIGNAL);
        if (current == -1) {
            fprintf(stderr, "Unable to send data \n");
            return -1;
        }
        if (current == 0) { //Me cerraron del otro lado
            return sent;
        }
        sent+=current;
    }
    return sent;
}

ssize_t s_recv(int fd, char* buffer, size_t len) {
    ssize_t received = 0;
    while (received < len) {
        ssize_t current = recv(fd,buffer+received,len-received, 0);
        if (current == -1) {
            fprintf(stderr, "Unable to receive data \n");
            return -1;
        }
        if (current == 0) {
            return received;
        }
        received+=current;
    }
    return received;
}

int main(int argc, char *argv[]) {
    
    if( argc != 3 ) {
        fprintf(stderr,"Invocación incorrecta");
        return -1;
    }

    const char* host = argv[1];
    const char* port = argv[2];

    struct addrinfo hints;
    struct addrinfo *result, *rp;

    int s_fd;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       /* Allows IPv4 */
    hints.ai_socktype = SOCK_STREAM; /* TCP*/
    hints.ai_flags = 0;              /* 0 is for client*/
    hints.ai_protocol = 0;           /* Any protocol */

    if ( getaddrinfo(host, port, &hints, &result) != 0 ) {
        fprintf(stderr,"Problemas con la conexión\n");
        return -1;
    }
    for (rp=result; rp != NULL; rp = rp->ai_next) {
        s_fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (s_fd == -1 ) {
            continue;
        }
        if (connect(s_fd, rp->ai_addr, rp->ai_addrlen) == -1 ) {
            close(s_fd);
        } else {
           break;
        }
    }

    freeaddrinfo(result);
    if( rp == NULL ) {
            fprintf(stderr,"No se pudo bindear \n");
            return -1;
    }


    //aca es donde hay que hacer todo el procesado.
    
    shutdown(s_fd, SHUT_RDWR);
    close(s_fd);
    return 0;
}