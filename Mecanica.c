#include <stdio.h>
#include <string.h>

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
    return (mecanica->tentativas >= 10 || mecanica->pontuacao >= 10);
}


int getPontuacao(MecanicaSimples *mecanica) {
    return mecanica->pontuacao;
}


int main() {
    MecanicaSimples jogo = criarMecanicaSimples();

    printf("Tentativa 1 (Errada): %d\n", jogar(&jogo, "gato", "cachorro"));
    printf("Tentativa 2 (Certa): %d\n", jogar(&jogo, "gato", "gato"));
    printf("Pontuacao atual: %d\n", getPontuacao(&jogo));
    printf("Jogo acabou? %d\n", acabou(&jogo));

    return 0;
}
