#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

// 1 on success 0 on failure
int leer(FILE* archivo, uint16_t* entero, long int* puntero) {
    fseek(archivo, *puntero, SEEK_SET);
    int r = fread(entero, sizeof(uint16_t,1,archivo));
    *puntero = ftell(archivo);
    if(r==1) 
        return 1;
    return 0;
}

void escribir(FILE* archivo, uint16_t entero, long int* puntero) {
    fseek(archivo, *puntero, SEEK_SET);
    fwrite(&entero, sizeof(uint16_t,1,archivo));
    *puntero = ftell(archivo);
}


int main() {
    FILE* archivo = fopen("archivo.dat", "r+");
    long int lectura = 0;
    long int escritura = 0;
    uint16_t numero = 0;
    while (leer(archivo,&numero,&lectura)) {
        if(numero %3 == 0){
            escribir(archivo, numero, &escritura);
        }
    }
    ftruncate(fileno(archivo),escritura);
    fclose(archivo);
    return 0;
}