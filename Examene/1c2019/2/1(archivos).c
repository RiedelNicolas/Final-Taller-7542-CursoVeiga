/*Escribir un programa C que procese el archivo “numeros.txt” sobre sí mismo (sin crear
archivos intermedios y sin subir el archivo a memoria). El procesamiento consiste en leer
grupos de 4 caracteres hexadecimales y reemplazarlos por los correspondientes dígitos
decimales (que representen el mismo número leído pero en decimal). */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


// Supongo que la cantidad total es multiplo de 4.
bool leerNumeros(char* string, unsigned int *puntero, FILE* archivo) {
    fseek(archivo,*puntero,SEEK_SET);
    void *r = fgets(string,4+1,archivo);
    *puntero = ftell(archivo);
    return ( r!=NULL );
}

void cargar_numeros(char* string, unsigned int* puntero, FILE* archivo) {
    fseek(archivo, *puntero, SEEK_SET);
    fputs(string, archivo);
    *puntero = ftell(archivo);
}

void generar_decimal(char* hexa, char* decimal) {
    char *end;
    long int  intAux = strtol(hexa,&end,16);
    char aux[6] = {0};
    sprintf(aux,"%ld",intAux);
    strcpy(decimal,"");
    for (size_t i = 0; i < (5 - strlen(aux)); i++) {
        strcat(decimal,"0");
    }
    strcat(decimal, aux);
}


int main(int argc, char* argv[]) {
    int puntero_lec = 0;
    int puntero_esc = 0;
    FILE* archivo = fopen("numeritos.txt","r+");
    if(archivo == NULL) return -1;
    char decibuff[6];
    char hexabuff[5];
    char* end;

    fseek(archivo, 0, SEEK_END);
    unsigned int originalFileSize = ftell(archivo);
    int newSize = (originalFileSize/4)*5;  //Pasamos de representar con 4 a representar con 5.
    ftruncate(fileno(archivo),newSize); // Agrando el archivo
    //tengo que escribir de atras para adelante asi no sobrescribo nada util.
    puntero_esc = newSize - 5; // voy a ir escribiendo de a 5.
    puntero_lec = originalFileSize-4; //Voy a ir leyendo de a 4
    while (puntero_lec >=0) {
        fseek(archivo,puntero_lec,SEEK_SET);
        leerNumeros(hexabuff, &puntero_lec, archivo);
        puntero_lec-=8;
        generar_decimal(hexabuff, decibuff);
        fseek(archivo,puntero_esc,SEEK_SET);
        cargar_numeros(decibuff, &puntero_esc, archivo);
        puntero_esc-=10;
    }
    fclose(archivo);
    return 0;
}