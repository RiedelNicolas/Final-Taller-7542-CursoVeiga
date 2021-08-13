/*Escriba una función ISO C llamada Replicar que reciba 1 cadena (S), dos índices (I1 e I2)
 y una cantidad (Q). La función debe retornar una copia de S salvo los caracteres 
 que se encuentran entre los índices I1 e I2 que serán duplicados Q veces. 
 Ej. replicar(“Hola”, 1, 2, 3) retorna “Hololola”.
*/
#include <stdio.h>

char* replicar (const char* S, size_t I1, size_t I2, size_t Q) {
    if(I1>=strlen(S) || I2>=strlen(S) || I2 < I1){
        fprintf(stderr, "Parametros incorrectos pai.");
        return NULL;
    }
    size_t len = (strlen(S) + ((Q-1)*(I1-I2+1)) +1);
    char* replicado = (char*) malloc(sizeof(char)*len);

    size_t j = 0;
    for (size_t i = 0; i < strlen(S); i++) {
        if (i < I1 || i> I2) {
            replicado[j] = S[i];
            j++;
            continue;
        }
        while (Q>0) {
            for (size_t k = I1; i <= I2; i++) {
                replicado[j]=S[k];
                j++;
            }
        }
        Q--;
    }   
}