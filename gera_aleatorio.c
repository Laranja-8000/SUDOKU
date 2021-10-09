#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
int sorterar_linhas_colunas(void){ 
    srand(time(NULL)); 
    int linha_sorteada, 
        coluna_sorteada, 
        i, 
        num_linhas_sorteadas[17], 
        num_colunas_sorteadas[17]; 
 
    for(i = 0; i < 17; i++){ 
        linha_sorteada = rand() % 10; 
        coluna_sorteada = rand() % 10; 
        num_linhas_sorteadas[i] = linha_sorteada; 
        num_colunas_sorteadas[i] = coluna_sorteada; 
    } 
 
    verificar_sorteio_linhas_colunas(num_linhas_sorteadas, num_colunas_sorteadas); 
} 
 
int verificar_sorteio_linhas_colunas(int num_linhas_sorteadas[], int num_colunas_sorteadas[]){ 
    int i,j,k=1; 
    for(i = 0; i < 17; i++){ 
        for(j = k; j < 17; j++){ 
            if(num_linhas_sorteadas[i] == num_linhas_sorteadas[j] && num_colunas_sorteadas[i] == num_colunas_sorteadas[j]){ 
                sorterar_linhas_colunas(); 
            } 
        } 
        k = k + 1; 
    } 
 
    for(i = 0; i<17; i++){ 
        printf("posicao %d - (linha,coluna): (%d, %d)\n", i+1, num_linhas_sorteadas[i], num_colunas_sorteadas[i]); 
    } 
     
} 
int main (void){ 
    sorterar_linhas_colunas(); 
}
