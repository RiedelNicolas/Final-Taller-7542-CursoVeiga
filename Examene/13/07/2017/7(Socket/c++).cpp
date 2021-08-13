#include <stdio.h>

class Socket {
private :
    int fd;

public : 
    Socket();
    Socket(Socket&&)noexcept; //contructor movimiento
    void shutdown(); //cierra el socket
    void connectTo(const char* host,const char* port);
    void bind(char* port);
    void listen(int qSize);
    void send(const void* buffer, size_t len);
    ssize_t recv(void* buffer, size_t len);

    Socket(const Socket&)=delete;
    Socket operator=(const Socket&)=delete;
    Socket operator=(const Socket&&)=delete;

    ~Socket();
};

int main (int argc, char* argv[]) {
    const char* ip = argv[1];
    const char* port = "8080";
    Socket s();
    s.connectTo(ip, port);
    char message[1024];
    strcpy(message,"get bla bla bla");
    s.send(message, strlen(message));
    s.recv(message, 1024);
    int end = 0
    for (size_t i = 0; i < 1024; i++){
        if(message[i=='\n'){
            end+=1;
        }else{
            end = 0;
        }
        printf("%c",message[i]);
        if(end == 2) break;
    }
    s.shutdown();
    return 0;
} 