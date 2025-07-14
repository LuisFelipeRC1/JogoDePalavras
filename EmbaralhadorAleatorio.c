#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>




void embaralharAleatorio(char *palavra) { // * é um ponteiro e modifica direto na memoria por isso não precisamos retornar um char 
    int tamanho = strlen(palavra);
    

    for (int i = 0; i < tamanho; i++) {
        int indiceAleatorio = rand() % tamanho;
        char temp = palavra[i];
        palavra[i] = palavra[indiceAleatorio];
        palavra[indiceAleatorio] = temp;
    }
  
}



int main() {

    char palavra[] = "programacao";
    
    printf("Palavra original: %s\n", palavra);
    embaralharAleatorio(palavra);
    printf("Palavra embaralhada: %s\n", palavra);

    return 0;
}
