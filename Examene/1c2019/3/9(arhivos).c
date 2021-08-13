/*Escriba una función ISO C que permita procesar un archivo texto que contenga frases (1
por línea) sobre sí mismo, sin generar archivos intermedios ni cargar el archivo completo a
memoria. El procesamiento consiste en eliminar las palabras de más de 3 letras de cada línea.
*/

#include <stdio.h>
#include <unistd.h>

void escribir(FILE* f, char c, long int *puntero) {
    fseek(f, *puntero, SEEK_SET);
    fputc(c,f);
    *puntero = ftell(f);
}

int leer(FILE* f, long int *puntero) {
    fseek(f, *puntero, SEEK_SET);
    int c = fgetc(f);
    *puntero = ftell(f);
    return c;
}

void procesar(FILE * archivo){
    long int escritura = 0;
    long int lectura = 0;
    char buffer[64];
    memset(buffer,0,64);

    int terminePalabra = 0; // 0 false, 1 true.
    int contador = 0;
    
    while (!feof(archivo) ) {
        int c = leer(archivo,&lectura);
        switch (terminePalabra) {
        case 1:
            if(contador <=3 ) {
                for (int i = 0 ; i< buffer; i++) {
                    escribir(archivo, buffer,&escritura);
                }
            }
            contador = 0;
            buffer[contador] = (char)c;
            contador++;
            break;
        case 0:
            if((char) c !=' ' && (char) c != '\n'){
                buffer[contador] = (char) c;
                contador++;
            }else{
                terminePalabra = 1; //true
            }
            break;
        }
    }
    if(contador <=3 && contador != 0) {
        for (int i = 0 ; i< buffer; i++) {
            escribir(archivo, buffer,&escritura);
        }

    ftruncate(fileno(archivo),escritura);
}

int main() {
    FILE* archivo = fopen("archivito.txt","r+");
    if (archivo == NULL) return -1;
    procesar(archivo);
    fclose(archivo);
}


