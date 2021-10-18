#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 9

void limpar_buffer(){
	/* Limpando o buffer */
	char buffer;
    do{
            buffer = getchar();
        }while(buffer != '\n');
}

int input_direcional(){
	char c;
	/* coloca o terminal em raw */
	system ("/bin/stty raw");
	
	if((c = getchar())=='\033'){
		c = getchar();
		if(c == '['){
			/* Um direcional foi detectado */
			printf("\b\b\b\b    \b\b\b\b");
			c = getchar();
			
			switch(c){
				case 'A':
					c = 1;
					break;

				case 'B':
					c = 2;
					break;

				case 'D':
					c= 3;
					break;

				case 'C':
					c=4;
					break;
			}
		}

	}
	else{
		printf("\b \b");
	}

	/* Retorna o terminal pra cooked */
	system ("/bin/stty cooked");
	
	return c;
}



void exibe_grade(int arranjo[N][N]){
	int i,j;

	system("clear");

	for(i=0;i<=12;i++){
		printf("\n");
		if(i%4==0) 
			printf(" -------------------------");

		
		else{
			for(j=0;j<13;j++){
				if(j%4 != 0)
					printf(" %d",arranjo[i-(1+i/4)][j-(1+j/4)]);
				else
					printf(" |");

			}
		}
	}
	puts("\n");
	
}


void show_ASCII(){
	int i;
	for(i=0;i<256;i++){
		printf("%d %c\n",i,i);
	}
}


void exibe_menu(int opt){
	
	int i;

	system("clear");
	opt = 3 - opt;
	printf("\nSUDOKU v0.0\n\n");
	printf("  INICIAR\n  HELP\n  SAIR\n");

	for(i=opt;i>=0;i--){
		printf("\033[F");
	}
	printf(">\b");
	

}

int menu_inicial(){
	int opcao=1, tecla_apertada=0;

	/*
	OPCOES:
	1 - INICIAR
	2 - AJUDA
	3 - FECHAR
	*/

	while(tecla_apertada!=13){

		exibe_menu(opcao);

		tecla_apertada = input_direcional();
		if(tecla_apertada==1){
			if(opcao>1){
				opcao--;
			}
		}
		if(tecla_apertada==2){
			if(opcao<3){
				opcao++;
			}
		}	
	}

	return opcao;
}

void help(){
	system("clear");
	printf("Sudoku, por vezes escrito Su Doku (数独 'sūdoku') é um jogo baseado na colocação lógica de números.\n");
	printf("O objetivo do jogo é a colocação de números de 1 a 9 em cada uma das células vazias numa grade de 9x9,\n"); 
	printf("constituída por 3x3 subgrades chamadas regiões. O quebra-cabeça contém algumas pistas iniciais,\n"); 
	printf("que são números inseridos em algumas células, de maneira a permitir uma indução ou dedução dos números\n");
	printf("em células que estejam vazias. Cada coluna, linha e região só pode ter um número de cada um dos 1 a 9.\n");
	printf("Resolver o problema requer apenas raciocínio lógico e algum tempo.\n\n");
	printf("Utilize as teclas direcionais para navegas pelas coordenadas da grade, e as teclas numéricas para preencher.\n");
	printf("O jogo encerra sozinho, uma vez que seja solucionado\n\n");
	printf("Pressione qualquer tecla para voltar ao menu inicial.\n");
	input_direcional();
}

 

void print(int arranjo[N][N])
{
    int i,j;
     for (i = 0; i < N; i++)
      {
         for (j = 0; j < N; j++)
            printf("%d ",arranjo[i][j]);
         printf("\n");
       }
}
 

int seguranca(int matriz[N][N], int linha,
                       int col, int num){

	/* Verifica se o conteúdo de uma posição é válido ou não */

    int iniciarLinha = linha - linha % 3,
                 iniciartCol = col - col % 3; 
    int x, i, j;

    for (x = 0; x <= 8; x++)
        if (matriz[linha][x] == num)
            return 0;
 
    for (x = 0; x <= 8; x++)
        if (matriz[x][col] == num)
            return 0;
   
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            if (matriz[i + iniciarLinha][j +
                          iniciartCol] == num)
                return 0;
 
    return 1;
}
 

int resolveSuduko(int matriz[N][N], int linha, int col)
{
     int num;

    if (linha == N - 1 && col == N)
        return 1; 

    if (col == N)
    {
        linha++;
        col = 0;
    }   

    if (matriz[linha][col] > 0)
        return resolveSuduko(matriz, linha, col + 1);
 
    for (num = 1; num <= N; num++)
    {   
        if (seguranca(matriz, linha, col, num)==1)
        {
            matriz[linha][col] = num;
            if (resolveSuduko(matriz, linha, col + 1)==1)
                return 1;
        }
        matriz[linha][col] = 0;
    }
    return 0;
}
 
int gera_jogo(int matriz[9][9])
{
    int i,j, numero;
    srand(time(NULL));
    numero = (rand()%9)+1;

    /* preenchendo a primeira diagonal */
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            while(seguranca(matriz,i,j,numero)==0){
                numero = (rand()%9)+1;
            }
            matriz[i][j] = numero;
        }
    }
    for(i=3;i<6;i++){
        for(j=3;j<6;j++){
            while(seguranca(matriz,i,j,numero)==0){
                numero = (rand()%9)+1;
            }
            matriz[i][j] = numero;
        }
    }
    for(i=6;i<9;i++){
        for(j=6;j<9;j++){
            while(seguranca(matriz,i,j,numero)==0){
                numero = (rand()%9)+1;
            }
            matriz[i][j] = numero;
        }
    }
    if (resolveSuduko(matriz, 0, 0)==1)
        return 1;
    return 0;
}

int verificar_sorteio_linhas_colunas(int num_linhas_sorteadas[], int num_colunas_sorteadas[]){ 
    int i,j,k=1; 
    for(i = 0; i < 17; i++){ 
        for(j = k; j < 17; j++){ 
            if(num_linhas_sorteadas[i] == num_linhas_sorteadas[j] && num_colunas_sorteadas[i] == num_colunas_sorteadas[j]){ 
                return 1; 
            } 
        } 
        k = k + 1; 
    } 
 
    return 0;    
}

void sorterar_linhas_colunas(int coordenadas_sorteadas[], int quantos){ 
    /* pega um array de 'quantos' inteiros e preenche com dezenas aleatórias únicas representando coordendas */

    int linha_sorteada, 
        coluna_sorteada, 
        i, 
        num_linhas_sorteadas[81], 
        num_colunas_sorteadas[81]; 

    srand(time(NULL)); 
 
 	do{
	    for(i = 0; i < quantos; i++){ 
	        linha_sorteada = rand() % 9; 
	        coluna_sorteada = rand() % 9; 
	        num_linhas_sorteadas[i] = linha_sorteada; 
	        num_colunas_sorteadas[i] = coluna_sorteada; 
	    } 
 	}
    while(verificar_sorteio_linhas_colunas(num_linhas_sorteadas, num_colunas_sorteadas)); 

    for(i = 0; i<quantos; i++){ 
        /* printf("posicao %d - (linha,coluna): (%d, %d)\n", i+1, num_linhas_sorteadas[i], num_colunas_sorteadas[i]); */
        coordenadas_sorteadas[i] = 10*num_linhas_sorteadas[i] + num_colunas_sorteadas[i]; 
    }
} 

/* ================================================================================================================== */
int main(){
	
	int next;
	int i, dificuldade;
	int coordenadas_sorteadas[81];
	for(i=0;i<81;i++) coordenadas_sorteadas[i] = -1;

	/* gera posições zeradas pelo parâmetro 'dificuldade' */
	dificuldade = 20;
	sorterar_linhas_colunas(coordenadas_sorteadas,dificuldade);

	/* a matriz contendo os conteúdos das casas do tabuleiro */
	int Jogo1[N][N]={ { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

    /* a matriz que diz quais coisas são fixas ou mutáveis */
    int Jogo2[N][N]={ { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

	/* inicializando as matrizes */
    gera_jogo(Jogo1);
	
	while((next=menu_inicial())!=3){
		if(next==1){			
			exibe_grade(Jogo1);
			input_direcional();
		}
		if(next==2){
			help();
		}
		if(next==3){			

		}
	}

	system("clear");

	return 0;
}
