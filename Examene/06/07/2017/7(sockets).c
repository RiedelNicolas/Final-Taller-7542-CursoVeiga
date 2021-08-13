#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

ssize_t s_send(int fd, char* buffer, size_t len){
    size_t sent = 0;
    while (sent < len) {
        ssize_t current =  send(fd,buffer+sent,len-sent,MSG_NOSIGNAL);
        if (current == -1){
            return -1;
        }else if(current == 0 ){
            break;
        }
        sent+=current;
    }
    return sent;
}


int main(int argc, char* argv[]) {
    char* port = argv[1];
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int s_fd, peer;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if (getaddrinfo(NULL, port, &hints, &result) == 0) {
        fprintf(stderr,"Problemas con la conexión\n");
        return -1;
    }

    for(rp=result; rp != NULL; rp = rp->ai_next) {
        s_fd = socket(rp->ai_family,rp->ai_socktype, rp->ai_protocol);
        if(s_fd == -1) {
            continue;
        } if(connect(s_fd,rp->ai_addr,rp->ai_addrlen)) {
            break;
        }
    }
    freeaddrinfo(result);

    if (rp == NULL) {
        fprintf(perror,"Couldnt bind");
        return -1;
    }

    listen(s_fd, 20); // Cantidad que quiero escuchar.

    while (1) {
        peer = accept(s_fd, NULL, NULL);
        if (peer == -1) {
            break;
        }
        char mensaje[50];
        strcpy(mensaje, "Conexion rechazada");
        s_send(peer,mensaje,strlen(mensaje)+1);
        shutdown(peer,SHUT_RDWR);
        close(peer);
        
    }

    shutdown(s_fd,SHUT_RDWR);
    close(s_fd);
}