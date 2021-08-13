//Recibo dos strings, tengo que duplicar las ocurrencias del segundo en el primero.
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char* argv[]) {

    if (argc !=3 ) {
        return -1;
    }

    char* a = argv[1];
    char* b = argv[2];

    for (size_t i = 0; i < strlen(a); i++) {
        printf("%c",a);
        bool repetir = true;
        for (size_t j = 0; j < strlen(b); j++) {
            if(a[i] != b[j]) {
                repetir = false;
                break;
            }
            if(repetir){
                printf(" %s",b);
            }
        }
    }
    return 0;    
}