#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PALAVRA 50

typedef struct {
    char palavras[100][MAX_PALAVRA];
    int quantidade;
} BancoDePalavras;

BancoDePalavras carregarBancoDePalavras(const char *caminho) {
    BancoDePalavras banco;
    banco.quantidade = 0;

    FILE *arquivo = fopen(caminho, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        exit(EXIT_FAILURE);
    }

    while (fgets(banco.palavras[banco.quantidade], MAX_PALAVRA, arquivo)) {
        banco.palavras[banco.quantidade][strcspn(banco.palavras[banco.quantidade], "\n")] = '\0';
        banco.quantidade++;
        if (banco.quantidade >= 100) break;
    }

    fclose(arquivo);
    return banco;
}

const char* getPalavraAleatoria(BancoDePalavras *banco) {
    if (banco->quantidade == 0) return NULL;
    int indice = rand() % banco->quantidade;
    return banco->palavras[indice];
}

int main() {
    

    BancoDePalavras banco = carregarBancoDePalavras("palavras.txt");

    printf("Palavra aleatória: %s\n", getPalavraAleatoria(&banco));

    return 0;
}