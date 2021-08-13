#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#define MAX_LINEA 2048

/*Escribir un programa ISO C que reciba por argumento el
 nombre de un archivo de texto y lo procese sobre sí mismo.
 (sin crear archivos intermedios ni subiendo todo su contenido a memoria).
 El procesamiento consiste en eliminar las líneas de 1 sola palabra.
*/

bool es_unica_palabra(char* string){
    for (size_t i = 0; i < strlen(string); i++){
        if(string[i]==' ') return false;
    }
    return true;
}

void escribir_linea(FILE* archivo, long int * pos_esc, char* linea){
    fseek(archivo, *pos_esc, SEEK_SET);
    fputs(linea, archivo);
    *pos_esc = ftell(archivo);
}

bool leer_linea (FILE* archivo, long int* pos_lectura, char* linea) {
    fseek(archivo, *pos_lectura, SEEK_SET);
    char* i = fgets(linea, MAX_LINEA, archivo);
    *pos_lectura = ftell(archivo);
    return (i!=NULL);
}

int main(int argc, char* argv[]){
    if(argc!=2) return -1;
    char* path = argv[1];
    FILE* archivo = fopen(path,"r+");
    if(archivo==NULL) return -1;
    long int pos_lec = 0;
    long int pos_esc = 0;
    char linea[MAX_LINEA];
    long int tam_final = 0;
    while(leer_linea(archivo, &pos_lec, linea)){
        if(!es_unica_palabra(linea)){
            escribir_linea(archivo, &pos_esc, linea);
            tam_final+=strlen(linea);
        }
    }
    ftruncate(fileno(archivo), sizeof(char)*(tam_final));
    fclose(archivo);
    return ;
}