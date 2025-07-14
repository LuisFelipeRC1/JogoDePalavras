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

void embaralharAleatorio(char *palavra) {
    int tamanho = strlen(palavra);
    

    for (int i = 0; i < tamanho; i++) {
        int indiceAleatorio = rand() % tamanho;
        char temp = palavra[i];
        palavra[i] = palavra[indiceAleatorio];
        palavra[indiceAleatorio] = temp;
    }
}

void adicionarPalavra(const char *caminho) {
    char novaPalavra[MAX_PALAVRA];
    printf("Digite a nova palavra para adicionar ao banco:\n (sem acento, sem letras maiúsculas) \n");
    scanf("%49s", novaPalavra);

    FILE *arquivo = fopen(caminho, "a");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo para escrita");
        return;
    }
    fprintf(arquivo, "%s\n", novaPalavra);
    fclose(arquivo);

    printf("Palavra '%s' adicionada com sucesso!\n", novaPalavra);
}


typedef struct {
    int pontuacao;
    int tentativas;
} MecanicaSimples;

MecanicaSimples criarMecanicaSimples() {
    MecanicaSimples m;
    m.pontuacao = 0;
    m.tentativas = 0;
    return m;
}

int jogar(MecanicaSimples *mecanica, const char *palavraOriginal, const char *tentativa) {
    mecanica->tentativas++;
    if (strcmp(palavraOriginal, tentativa) == 0) {
        mecanica->pontuacao++;
        return 1;
    }
    return 0;
}

int acabou(MecanicaSimples *mecanica) {
    return (mecanica->tentativas >= 10 || mecanica->pontuacao >= 5);
}


void iniciarJogo() {
    
    BancoDePalavras banco = carregarBancoDePalavras("palavras.txt");


    MecanicaSimples mecanica = criarMecanicaSimples();
    char matriz[10][3][MAX_PALAVRA];

    char palavraOriginal[MAX_PALAVRA];
    char palavraEmbaralhada[MAX_PALAVRA];
    char tentativa[MAX_PALAVRA];

    printf("Bem-vindo ao jogo de palavras embaralhadas!\n");
    printf("=== Regras do JOGO ===\n");
    printf("O jogador tem 10 tentativas para acertar 5 palavras embaralhadas\n");

    while (!acabou(&mecanica)) {
    
        strcpy(palavraOriginal, getPalavraAleatoria(&banco));
        strcpy(palavraEmbaralhada, palavraOriginal);

     
        embaralharAleatorio(palavraEmbaralhada);

        printf("\nAdivinhe a palavra embaralhada: %s\n", palavraEmbaralhada);
        printf("Digite sua tentativa: ");
        scanf("%49s", tentativa);

        strcpy(matriz[mecanica.tentativas][0], palavraOriginal);
        strcpy(matriz[mecanica.tentativas][1], palavraEmbaralhada);
        strcpy(matriz[mecanica.tentativas][2], tentativa);

        if (jogar(&mecanica, palavraOriginal, tentativa)) {
            printf("Voce acertou!\n");
        } else {
            printf("Tente novamente.\n");
        }
    }

    printf("\n      === Matriz de Palavras ===     \n");
    printf("%-15s %-15s %-15s\n", "Original", "Embaralhada", "Tentativa");
    for (int i = 0; i < mecanica.tentativas; i++) {
        printf("%-15s %-15s %-15s\n", matriz[i][0], matriz[i][1], matriz[i][2]);
    }
    
    if (mecanica.pontuacao >= 5) {
        printf("\nVoce ganhou!!!\n");
    } else {
        printf("\nVoce perdeu!!!\n");
    }
    printf("\nFim do jogo! Pontuacao final: %d\n", mecanica.pontuacao);
}


int main() {
    srand(time(NULL));
    int opcao;

    do {
        printf("\n=== MENU ===\n");
        printf("1 - Jogar\n");
        printf("2 - Adicionar nova palavra\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                iniciarJogo();
                break;
            case 2:
                adicionarPalavra("palavras.txt");
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
