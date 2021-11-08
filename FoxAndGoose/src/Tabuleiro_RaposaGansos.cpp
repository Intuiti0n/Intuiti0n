#include <cstdio>  //input-output - necessario para scanf e printf
#include <cstdlib> //standard lib contém função PAUSE

#define N 7

short int tabul[N][N];  // tabuleiro do Jogo Raposa e Gansos com inteiros
                        // 0- vazio, 1-peça jog1, 2-peça jog2
char conv(short int peca) //converte o numero da peça num simbolo 
{
   if (peca==1) return 'G';      //Ganso
   else if (peca==2) return 'R'; //Raposa   
   else return ' ';    			 //posição livre
}
void inicia_tabul(void) //inicia o tabuleiro com espaços vazios (tabul[i][j]=0) ou R (tabul[i][j]=1) ou G (tabul[i][j]=2)
{
  int i, j;
  for(i=1; i<N+1; i++){
  	for(j=1; j<N+1; j++) {
		if(i==3&&j==4) tabul[i][j] = 2;//desenha a raposa na posição 3,4	
		if(i>=5) tabul[i][j] = 1;  //desenha os 13 gansos na posição inicial, que é a partir da linha 5 ate ao fim do tabuleiro 
		}
	}      
}

void linha_topo(void){ //1ª linha do tabuleiro, por baixo dos numeros
	for(int j=1;j<N-3;j++) {
    	if(j==1) printf("%c",218); //canto superior esquerdo do tabuleiro
    	printf("%c%c%c",196,196,196); //caractere central(---)
    	if(j==N-4) printf("%c\n",191); //canto superior direito do tabuleiro
		if(j!=N-4)printf("%c",194); //caractere central seguinte "T"
		}}
void linha_3(void){ 			 //desenha a linha que separa o topo do meio do tabuleiro, ou seja, 
		for(int j=1;j<N+1;j++) { //separa as elementos que estao na linha 2 dos que estao na linha 3. 
    	if(j==1) printf("%c",218); //canto esquerdo da linha
    	printf("%c%c%c",196,196,196); //caractere central(---)
    	if(j==N) printf("%c\n",191); //canto direito da linha
		if(j<N) if(j<N-5||j>N-2)printf("%c",194); else printf("%c",197);//caractere central seguinte (194= "T" ; 197= "+")
		} 
}

void linha_central_topo(void){ //desenha |---|---|---| com caracteres ASCII
	for(int j=1;j<N-3;j++) {
    	if(j==1) printf("%c",195); //canto esquerdo (|-)
    	printf("%c%c%c",196,196,196); //caractere central(---)
    	if(j==N-4) printf("%c\n",180); //canto direito (-|)
		if(j!=N-4)printf("%c",197); //caractere central seguinte (+)
		}
}

void linha_central_meio(void){ //desenha |---|---|---|---|---|---|---| com caracteres ASCII
	printf(" "); //espaço entre o limite esquerdo do ecrã e o tabuleiro
	for(int j=1;j<N+1;j++){
    	if(j==1) printf("%c",195); //canto esquerdo (|-)
    	printf("%c%c%c",196,196,196); //caractere central(---)
    	if(j==N) printf("%c\n",180); //canto direito (-|)
		if(j!=N)printf("%c",197); //caractere central seguinte (+)
	}
}

void linha_meio_final(void){ //traço que separa a linha 5 da linha 6
	for(int j=1;j<N+1;j++) {
    	if(j==1) printf("%c",192); //canto inferior esquerdo  |_
    	printf("%c%c%c",196,196,196); //caractere central(---)
    	if(j==N) printf("%c\n",217); //canto inferior direito   _|
		if(j<N) if(j<N-5||j>N-2)printf("%c",193); else printf("%c",197);//caractere central seguinte (193= "_|_"; 197= "+")
		} 
}

void linha_final(void){ //ultima linha do tabuleiro
	for(int j=1;j<N-3;j++) {
    	if(j==1) printf("%c",192); //canto inferior esquerdo do tabuleiro
    	printf("%c%c%c",196,196,196); //caractere central(---)
    	if(j==N-4) printf("%c\n",217); //canto inferior direito do tabuleiro
		if(j!=N-4)printf("%c",193); //caractere central seguinte "T" invertido
		}
}


void mostra_tabul(void){
		printf("  ");for(int num=0;num<N;num++){printf(" %d  ",num+1); if(num==N-1) printf("\n");} //Imprime os numeros de 1 ate N(N=7 neste caso) por cima do tabuleiro
     	printf("         "); linha_topo(); //Desenha a 1ª linha do tabuleiro. ("         |---|---|---|\n");
      for(int i=1; i<N+1; i++) {
          
		 if(i<3) {
		 		printf("%c      ",i+48);//numeros a esquerda 1,2,3,4,5,6,7
		 		for(int j=3; j<6; j++){ 
         		if(j==3) printf("  ");//espaçamento entre linhas
         		else printf(" ");
         		printf("%c %c",179,conv(tabul[i][j])); } //desenha as barras verticais e adiciona uma posição da matriz 
        		printf(" %c	      %c",179,i+48); //desenha a ultima barra da linha e o numero à direita do tabuleiro
				if(i<2)  {printf("\n         ");linha_central_topo();} //desenha |---|---|---|
				if(i==2) {printf("\n "); linha_3();} //muda de linha porque o traço que separa a linha 2 da linha 3 é diferente dos restantes
         }
         if(i>=3&&i<=5) { 
         	printf("%c",i+48);//desenha numero a esquerda do tabuleiro
		 		for(int j=1; j<N+1; j++) {printf("%c %c ",179,conv(tabul[i][j]));}//desenha as barras verticais(|) e adiciona posiçoes da matriz
        		if(i<=4) {printf("%c%c\n",179,i+48); linha_central_meio();} //desenha a ultima barra vertical da linha, o nº à direita e o traço da linha seguinte
				if(i>4) {printf("%c%c\n ",179,i+48); linha_meio_final(); }//desenha o ultimo traço do meio do tabuleiro |___|___+___+___+___+___|___|
         }
         if(i>5) {
         printf("%c      ",i+48); //desenha numero a esquerda do tabuleiro
		 		for(int j=3; j<6; j++){
		 		if(j==3) printf("  "); //espaçamento no 1º caractere para alinhar o tabuleiro	
		 		else printf(" ");//espaçamento dentro do tabuleiro
        		printf("%c %c",179, conv(tabul[i][j]));  } //desenha as barras verticais e adiciona posiçoes da matriz 
        		if(i==6) {printf(" %c        %c\n	 ",179,i+48);linha_central_topo();} //desenha a ultima barra vertical e o traço da linha seguinte
        		if(i==7) {printf(" %c        %c\n	 ",179,i+48); linha_final();}//desenha a ultima barra da linha e o ultimo traço do tabuleiro-> |___|___|___|
				}
	}
		printf("  ");
		for(int num=0;num<N;num++){printf(" %d  ",num+1); if(num==N-1) printf("\n");} //Imprime os numeros de 1 ate N por baixo do tabuleiro
}
int main(){
	inicia_tabul(); //preenche o tabuleiro com as peças na posiçao inicial de jogo
	mostra_tabul(); //desenha o tabuleiro com as posiçoes do inicia_tabul() preenchidas
	
}
