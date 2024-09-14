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
apenas os movimentos possiveis. (feito)
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

// Movimentos possíveis do cavalo (Anda em L)
int movimentos[8][2] = {
    {2, 1}, {2, -1}, //Lado Direito
    {-2, 1}, {-2, -1}, //Lado Esquerdo
    {1, 2}, {-1, 2}, //Lado Inferior
    {-1, -2}, {1, -2} //Lado Superior
};


int validaMovimento(int x, int y, int novoX, int novoY, int tabuleiro[TAM][TAM]){
     if (novoX >= 0 && novoX < TAM && novoY >= 0 && novoY < TAM && tabuleiro[novoX][novoY] == 0) {
        for (int i = 0; i < 8; i++) {
            int dx = movimentos[i][0];
            int dy = movimentos[i][1];
            if (x + dx == novoX && y + dy == novoY) {
                    return 1;
                }
            }
        }

    return 0;
}

void imprimeMenu(int tabuleiro[TAM][TAM], int x, int y){
    for (int i = 0; i < 8; i++) {
        int novoX = x + movimentos[i][0];
        int novoY = y + movimentos[i][1];
        if (validaMovimento(x, y, novoX, novoY, tabuleiro)) {
            printf("%d , %d\n", novoX, novoY);
        }
    }
}

void atualizaPosicao(int **P, int novoX, int novoY, int tabuleiro[TAM][TAM]){
    **P = 0;  // Marca a posição anterior como visitada
    *P = &tabuleiro[novoX][novoY];  // Atualiza o ponteiro para a nova posição
    **P = 1;  // Marca a nova posição do cavalo
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

    posicao_inicialX = rand() % TAM;
    posicao_inicialY = rand() % TAM;
    tabuleiro[posicao_inicialX][posicao_inicialY] = 1; /*Substitui a posicao do cavalo por 1*/
    P = (int**)&tabuleiro[posicao_inicialX][posicao_inicialY];

    printf("Tabuleiro inicial:\n");
    imprimeTabuleiro(tabuleiro);

    do {
        printf("Tabuleiro atual:\n");
        imprimeTabuleiro(tabuleiro);

        printf("Movimentos possíveis:\n");
        imprimeMenu(tabuleiro, posicao_inicialX, posicao_inicialY);

        printf("Escolher movimento (1) ou sair (0):\n");
        scanf("%d", &opcao);

        if(opcao == 0){
            break;
        } else if (opcao == 1) {
            printf("Escolha um movimento (x y):\n");
            scanf("%d %d", &posicaoX, &posicaoY);

            if (validaMovimento(posicao_inicialX, posicao_inicialY, posicaoX, posicaoY, tabuleiro) == 0) {
            printf("Movimento inválido.\n");
            }   else {
            atualizaPosicao(P, posicaoX, posicaoY, tabuleiro);
            posicao_inicialX = posicaoX;
            posicao_inicialY = posicaoY;
            }
        } else {
            printf("Opção inválida.\n");
        }

        system("cls"); //limpa o terminal antes da proxima ação

    } while (1); 

    return 0;

}
