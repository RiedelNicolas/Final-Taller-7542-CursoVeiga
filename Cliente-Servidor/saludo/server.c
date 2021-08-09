#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

#define BUF_SIZE 500

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

int main (int argc, char* argv[]) {
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int s_fd, peer;

    if (argc != 2) {
        fprintf(stderr,"Invocación incorrecta");
        return -1;
    }

    const char* port = argv[1];

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if (getaddrinfo(NULL, port, &hints, &result)) {
        fprintf(stderr,"Problemas con la conexión\n");
        return -1;
    }

    for (rp = result; rp!=NULL; rp = rp->ai_next) {
        s_fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if(s_fd == -1) {
            continue;
        }
        int val = 1;
        setsockopt(s_fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)); // Para reconcetar?
        if (bind(s_fd, rp->ai_addr, rp->ai_addrlen) == -1) {
            close(s_fd);
        }else {
            break; //success
        }
    }

    freeaddrinfo(result);

    if (rp == NULL) {
        fprintf(perror,"Couldnt bind");
        return -1;
    }

    listen(s_fd, 1); // Cantidad que quiero escuchar.
    peer = accept(s_fd,NULL, NULL); //Esta es bloqueante, hasta que llega uno.
    if(peer == -1) {
        fprintf(stderr,"Problemas con la conexión\n");
        close(s_fd);
        return -1;
    }
    //aca es donde hay que hacer toda la bola?
    
    char saludo[600];
    strcpy(saludo, "Hola cliente, soy el server");
    s_send(s_fd, saludo, strlen(saludo));

    shutdown(s_fd,SHUT_RDWR);
    shutdown(peer,SHUT_RDWR);
    close(peer);
    close(s_fd);
    return 0;  
}