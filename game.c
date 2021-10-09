#include <stdio.h>
#include <stdlib.h>

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



void exibe_grade(){
	int i,j;

	system("clear");

	for(i=0;i<=12;i++){
		printf("\n");
		if(i%4==0) 
			printf(" -------------------------");

		
		else{
			for(j=0;j<13;j++){
				if(j%4 != 0)
					printf(" %d",0);
				else
					printf(" |");

			}
		}
	}
	puts("\n");
	input_direcional();
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


int main(){
	
	int next;

	
	while((next=menu_inicial())!=3){
		if(next==1){
			exibe_grade();

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