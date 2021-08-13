#include <stdlib.h>
#include <stdio.h>

int main(){
    char * x = "FFFF\0";
    char* end;
    printf("El hexa %s\n",x);
    printf("es : %lu ", strtol(x,&end,16));
    return 0;
}