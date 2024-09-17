/*  Trabalho 1 - Algoritmos e Programacao II - Ponteiros

    ==========="O Jogo do Passeio do Cavalo"============

    Grupo:
        >> Ana Paula Gondin Bastos;
        >> Felipe Moneda Gilioli;
        >> Vitor Hugo Ribeiro Franco;                  */


#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <windows.h>

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
            int dx = *(*(movimentos + i) + 0);
            int dy = *(*(movimentos + i) + 1);
            if (x + dx == novoX && y + dy == novoY) {
                    return 1;
                }
            }
        }
    return 0;
}

void imprimeMenu(int tabuleiro[TAM][TAM], int x, int y, int *cont){
    *cont = 0;
    for (int i = 0; i < 8; i++) {
        int novoX = x + *(*(movimentos + i) + 0);
        int novoY = y + *(*(movimentos + i) + 1);
        if (validaMovimento(x, y, novoX, novoY, tabuleiro)) {
            printf("%d , %d\n", novoX, novoY);
            (*cont)++;
        }
    }
}

void atualizaPosicao(int **P, int novoX, int novoY, int tabuleiro[TAM][TAM]){
    **P = 1;  // Marca a posição anterior como visitada
    *P = &tabuleiro[novoX][novoY];  // Atualiza o ponteiro para a nova posição
    **P = 2;  // Marca a nova posição do cavalo
}

int tabuleiroCompleto(int tabuleiro[TAM][TAM]){
    for(int i=0; i<TAM; i++){
        for(int j=0; j<TAM; j++){
            if(tabuleiro[i][j] == 0){
                return 0;
            }
        }
    }
    return 1;
}

int main(){

    setlocale(LC_ALL,"portuguese");
    srand(time(NULL));

    int tabuleiro[TAM][TAM];
    int opcao; 
    int posicao_inicialX, posicao_inicialY;
    int posicaoX, posicaoY; 
    int *P; 
    int contador = 10; //contador de movimentos válidos disponíveis

    for(int i=0; i<TAM; i++){ 
        for(int j=0; j<TAM; j++){
            tabuleiro[i][j] = 0;
        }
    }

    posicao_inicialX = rand() % TAM;
    posicao_inicialY = rand() % TAM;
    tabuleiro[posicao_inicialX][posicao_inicialY] = 2; /*Substitui a posicao do cavalo por 2*/
    P = &tabuleiro[posicao_inicialX][posicao_inicialY];

    printf("Tabuleiro inicial:\n");
    imprimeTabuleiro(tabuleiro);

    do {

        if(tabuleiroCompleto(tabuleiro)){
            printf("\nTabuleiro completo. Parabéns, você ganhou!!!\n");
            break;
        }

        printf("Tabuleiro atual:\n");
        imprimeTabuleiro(tabuleiro);
        
        printf("Movimentos possíveis:\n");
        imprimeMenu(tabuleiro, posicao_inicialX, posicao_inicialY, &contador);

        if(contador == 0){
            system("cls");
            printf("Tabuleiro atual:\n");
            imprimeTabuleiro(tabuleiro);
            printf("\nNão há mais movimentos. Você perdeu!\n");
            break; 
        }

        printf("Escolher movimento (1) ou sair (0):\n");
        scanf("%d", &opcao);

        if(opcao == 0){
            break;
        } else if (opcao == 1) {
            printf("Escolha um movimento (x y):\n");
            scanf("%d %d", &posicaoX, &posicaoY);

            if (validaMovimento(posicao_inicialX, posicao_inicialY, posicaoX, posicaoY, tabuleiro) == 0) {
                printf("Movimento inválido.\n");
                Sleep(2000);
            } else {
            atualizaPosicao(&P, posicaoX, posicaoY, tabuleiro);
            posicao_inicialX = posicaoX;
            posicao_inicialY = posicaoY;
            }
        } else {
            printf("Opção inválida.\n");
            Sleep(2000); 
        }

        system("cls"); //limpa o terminal antes da proxima ação

    } while (1);

    return 0;

}
