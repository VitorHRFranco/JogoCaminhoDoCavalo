/*  Trabalho 1 - Algoritmos e Programa��o II - Ponteiros

    ==========="O Jogo do Passeio do Cavalo"============

    Grupo:
        >> Ana Paula Gondin Bastos;
        >> Felipe Moneda Gilioli;
        >> Vitor Hugo Ribeiro Franco;                  */

/*
i. Ao iniciar o programa o cavalo ira iniciar em uma posicao aleatoria.(feito)
a. O tabuleiro deve ser impresso para o usuario.(feito)
b. O tabuleiro deve ser uma matriz 4x4.(feito)
ii. Os possiveis movimentos que o cavalo pode fazer deve aparecer em um menu e
apenas os movimentos possiveis.
a. O usuario deve escolher um dos movimentos do menu.
b. O cavalo nao pode passar os limites do tabuleiro.
c. Onde o cavalo ja passou deve ser marcado como uma posicao que nao
pode ser explorada.
d. O tabuleiro deve ser impresso para o usuario a cada movimento feito.
e. Um ponteiro P deve ser utilizado para guardar a posicao do cavalo.
f. Toda movimentacao do cavalo deve ser feita por aritmetica de ponteiro e
pelo ponteiro P. O trabalho que nao atender esses requisitos tera nota zero.
iii. O jogo finaliza quando:
a. O usuario nao tiver mais movimento para fazer.
b. O usuario ganha quando todas as posicoes do tabuleiro estiverem
marcadas.
c. O usuario perde se nao tiver mais jogadas e tiver posicoes no tabuleiro em
aberto.
d. No fim do jogo deve ser impresso ao usuario se ele perdeu ou ganhou.
*/


#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

#define TAM 4

void imprimeTabuleiro(int tabuleiro[TAM][TAM]){
        for(int i=0; i<TAM; i++){
            for(int j=0; j<TAM; j++){
                printf(" %d", tabuleiro[i][j]);
            }
            printf("\n");
        }
}

void imprimeMenu(){

}

void atualizaPosicao(int **P, int novoX, int novoY, int tabuleiro[TAM][TAM]){
    **P = 0;  // Marca a posição anterior como visitada
    *P = &tabuleiro[novoX][novoY];  // Atualiza o ponteiro para a nova posição
    **P = 1;  // Marca a nova posição do cavalo
}

//Verificando se o movimento esta dentro dos limites do tabuleiro (coordenada entre 0 e 3 nos eixos x e y pois eh uma matriz 4x4); se a posição já não foi ocupada (posicao vazia, representada por '.');
//Retorna o quando o movimento for invalido;

int validaMovimento(int x, int y, int tabuleiro[TAM][TAM]){
    if (x >= 0 && x <= 3 && y >= 0 && y <= 3 && tabuleiro[x][y] == '.') {
        return 1;
    }
    return 0;
}


int main(){

    srand(time(NULL));

    int tabuleiro[TAM][TAM];
    int opcao; //armazena escolha do menu
    int posicao_inicialX, posicao_inicialY;
    int posicaoX, posicaoY; //posicoes atualizadas
    int **P; //ponteiro que guarda a posicao do cavalo

    for(int i=0; i<TAM; i++){ /*Preenche a matriz com 0*/
        for(int j=0; j<TAM; j++){
            tabuleiro[i][j] = 0;
        }
    }

    posicao_inicialX = rand() % 4;
    posicao_inicialY = rand() % 4;
    tabuleiro[posicao_inicialX][posicao_inicialY] = 1; /*Substitui a posicao do cavalo por 1*/
    P = (int**)&tabuleiro[posicao_inicialX][posicao_inicialY];

    printf("Tabuleiro inicial:\n");
    imprimeTabuleiro(tabuleiro);

    do {
        printf("Tabuleiro atual:\n");
        imprimeTabuleiro(tabuleiro);

        printf("Escolha um movimento OU Digite 0 para Sair: ");
        scanf("%d", &opcao);

        if(validaMovimento(posicaoX, posicaoY, tabuleiro) == 0){
        printf("Movimento inválido.");
        } else {
            atualizaPosicao(&P, posicaoX, posicaoY, tabuleiro);

            posicao_inicialX = posicaoX;
            posicao_inicialY = posicaoY;
        }

        system("cls"); //limpa o terminal antes da proxima ação

    } while (opcao != '\0'); // Sair do jogo quando jogador digitar 0;

    return 0;

}
