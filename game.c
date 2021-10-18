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

void gotoxy(int x,int y)
{
    printf("%c[%d;%df",0x1B,y,x);
}

void exibe_grade(int arranjo[N][N], int matriz_secundaria[N][N]){
	int i,j,aux;

	system("clear");

	for(i=0;i<=12;i++){
		printf("\n");
		if(i%4==0) 
			printf(" -------------------------");

		
		else{
			for(j=0;j<13;j++){
				if(j%4 != 0)
					if(arranjo[i-(1+i/4)][j-(1+j/4)]==0){
						printf(" -");
					}
					else{
						aux = arranjo[i-(1+i/4)][j-(1+j/4)];
						arranjo[i-(1+i/4)][j-(1+j/4)] = 0;
						if(seguranca(arranjo,i-(1+i/4),j-(1+j/4),aux)==0){
							if(matriz_secundaria[i-(1+i/4)][j-(1+j/4)]==1){
								printf("\033[0;31m"); /* vermelho */
							}
						}
						else{
							if(matriz_secundaria[i-(1+i/4)][j-(1+j/4)]==1)
								printf("\033[0;32m"); /* verde */
						}
						arranjo[i-(1+i/4)][j-(1+j/4)] = aux;
						printf(" %d",arranjo[i-(1+i/4)][j-(1+j/4)]);
						printf("\033[0;37m"); /* branco */
					}
				else
					printf(" |");
			}
		}
	}
	puts("\n");	
	
}


void show_ASCII(){
	

}


void exibe_menu(int opt){
	
	int i;

	system("clear");
	opt = 3 - opt;
	printf("\nSUDOKU v0.0\n\n");
	printf("  JOGAR\n  HELP\n  SAIR\n");

	for(i=opt;i>=0;i--){
		printf("\033[F");
	}
	printf(">\b");
}

int menu_inicial(){
	int opcao=1, tecla_apertada=0;

	/*
	OPCOES:
	1 - JOGAR
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
	printf("O jogo encerra sozinho, uma vez que seja solucionado.\n\n");
	printf("Em qualquer momento durante o jogo, aperte a Barra de Espaço para retornar ao menu principal\n\n");
	printf("Pressione qualquer tecla para voltar ao menu inicial.\n");
	input_direcional();
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

    /* a matriz contendo os conteúdos das casas do tabuleiro */
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			matriz[i][j] = 0;
		}
	}
    
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



int game_over(int matriz[9][9]){

	int i,j,aux;
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			if(matriz[i][j]==0) 
				return 1;
			else{
				aux = matriz[i][j];
				matriz[i][j]=0;
				if((seguranca(matriz,i,j,aux))==0){
					matriz[i][j] = aux;
					return 1;
				}
				matriz[i][j] = aux;
			}
		}
	}
	return 0;
}

/* ================================================================================================================== */

void movimento(int matriz[9][9], int matriz_secundaria[9][9]){
	/* Movimentação pelas casas do tabuleiro. Chama a função exibe_grade() passando as coordenadas do cursor */
	
	int x=4, y=3;
	int tecla_apertada=0;
	
	exibe_grade(matriz,matriz_secundaria);
	gotoxy(x,y);

	x = 0;
	y = 0;

	while(tecla_apertada!=32 && game_over(matriz)!=0){
		tecla_apertada = input_direcional();

		if(tecla_apertada == 2){ /* baixo */
			if(y<8){
				y++;
			}
		}
		if(tecla_apertada ==1){ /* cima */
			if(y>0){
				y--;
			}
		}
		if(tecla_apertada == 3){ /* esquerda */
			if(x>0){
				x--;
			}
		}
		if(tecla_apertada == 4){ /* direita */
			if(x<8){
				x++;
			}
		}

		if(tecla_apertada>='0' && tecla_apertada<='9'){
			if(matriz_secundaria[y][x]==1){
				matriz[y][x] = tecla_apertada-48;
			}
		}


		exibe_grade(matriz,matriz_secundaria);

		/* calculo pra posicionar o cursor no tabuleiro impresso */

		gotoxy(4 + 2*(x + (x/3)), 3 + y + y/3 );

	}

	if(game_over(matriz)==0){
		system("clear");
		gotoxy(0,0);
		printf("Parabens, você venceu! *clap clap*\n");
		input_direcional();
	}
	gotoxy(0,0);
}



/* ================================================================================================================== */

void sorterar_linhas_colunas(int coordenadas_sorteadas[], int quantos){ 
    /* pega um array de 'quantos' inteiros e preenche com dezenas aleatórias únicas representando coordendas */

    int linha_sorteada, 
        coluna_sorteada, 
        i, 
        num_linhas_sorteadas[81], 
        num_colunas_sorteadas[81]; 

    for(i=0;i<81;i++) coordenadas_sorteadas[i] = -1;
    srand(time(NULL)); 
 
 	do{
	    for(i = 0; i <= quantos; i++){ 
	        linha_sorteada = rand() % 9; 
	        coluna_sorteada = rand() % 9; 
	        num_linhas_sorteadas[i] = linha_sorteada; 
	        num_colunas_sorteadas[i] = coluna_sorteada; 
	    } 
 	}
    while(verificar_sorteio_linhas_colunas(num_linhas_sorteadas, num_colunas_sorteadas)); 

    for(i = 0; i<=quantos; i++){ 
        /* printf("posicao %d - (linha,coluna): (%d, %d)\n", i+1, num_linhas_sorteadas[i], num_colunas_sorteadas[i]); */
        coordenadas_sorteadas[i] = 10*num_linhas_sorteadas[i] + num_colunas_sorteadas[i]; 
    }
} 

void retira_casas(int coordenadas_sorteadas[], int matriz[9][9], int matriz_secundaria[9][9], int n){

	int i,j;

	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			matriz_secundaria[i][j] = 0;
		}
	}

	for(i=0;i<=n;i++){
		matriz[coordenadas_sorteadas[i]/10][coordenadas_sorteadas[i]%10] = 0;
		matriz_secundaria[coordenadas_sorteadas[i]/10][coordenadas_sorteadas[i]%10] = 1;
	}
}

/* ================================================================================================================== */
void exibe_dificuldades(int opt){
	
	int i;

	system("clear");
	opt = 3 - opt;
	printf("\nQual dificuldade?\n\n");
	show_ASCII();
	printf("  Fácil\n  Médio\n  Hardcore\n");

	for(i=opt;i>=0;i--){
		printf("\033[F");
	}
	printf(">\b");
}

int dificuldade(){
	int opcao=1, tecla_apertada=0;

	/*
	OPCOES:
	1 - Fácil (60 pistas)
	2 - Médio (40 pistas)
	3 - Hardcore (20 pistas)
	*/

	while(tecla_apertada!=13){

		exibe_dificuldades(opcao);

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


/* ================================================================================================================== */
int main(){
	
	int next;
	int i, dificuldade_selecionada;
	int coordenadas_sorteadas[81];
	

	

	int Jogo1[N][N];

    /* a matriz que diz quais casas são fixas ou mutáveis */
    int Jogo2[N][N];

	    
	next = menu_inicial();	

	while(next!=3){
		if(next==1){	
			
			gera_jogo(Jogo1);

			/* gera posições zeradas pelo parâmetro 'dificuldade' */
			/* menor que 11 trava o jogo (bug)*/
			dificuldade_selecionada = dificuldade();

			sorterar_linhas_colunas(coordenadas_sorteadas,1+dificuldade_selecionada*20);

    		retira_casas(coordenadas_sorteadas,Jogo1,Jogo2,1+dificuldade_selecionada*20);

    		
    		
			movimento(Jogo1,Jogo2);
			
		}
		if(next==2){
			help();
		}
		if(next==3){			

		}

		next = menu_inicial();
	}

	system("clear");
	

	return 0;
}
