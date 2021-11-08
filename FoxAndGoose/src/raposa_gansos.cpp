#include <cstdio>  //input-output - necessario para scanf e printf
#include <cstdlib> //standard lib contém função PAUSE

#define N 7

short int tabul[N][N];  // tabuleiro do Jogo Raposa e Gansos com inteiros
                        // 0- vazio, 1-peça jog1, 2-peça jog2

char conv(short int peca)
{
   if (peca==1) return 'R';    
   else if (peca==2) return 'G';    
   else return ' ';    
}

void inicia_tabul(void) //inicia o tabuleiro com tudo a zero ou tudo a R (tabul[i][j]=1) ou igual a G (=2)
{
  int i, j;

  for(i=0; i<N; i++)
    for(j=0; j<N; j++) 
       tabul[i][j] = 0;                   
}

void linha_topo(void){ //1ª linha do tabuleiro
	for(int j=0;j<N-4;j++) {
    	if(j==0) printf("%c",218); //canto superior esquerdo do tabuleiro
    	printf("%c%c%c",196,196,196); //caractere central(-)
    	if(j==N-5) printf("%c\n",191); //canto superior direito
		if(j!=N-5)printf("%c",194); //caractere central seguinte
		}}
void linha_3(void){
		for(int j=0;j<N;j++) {
    	if(j==0) printf("%c",218); //canto superior esquerdo do tabuleiro
    	printf("%c%c%c",196,196,196); //caractere central(-)
    	if(j==N-1) printf("%c\n",191); //canto superior direito
		if(j<N-1) if(j<N-6||j>N-3)printf("%c",194); else printf("%c",197);//caractere central seguinte
		} 
}

void linha_central_topo(void){
	for(int j=0;j<N-4;j++) {
    	if(j==0) printf("%c",195); //canto superior esquerdo do tabuleiro
    	printf("%c%c%c",196,196,196); //caractere central(-)
    	if(j==N-5) printf("%c\n",180); //canto superior direito
		if(j!=N-5)printf("%c",197); //caractere central seguinte
		}
}

void linha_central_meio(void){
	printf(" ");
	for(int j=0;j<N;j++){
    	if(j==0) printf("%c",195); //canto esquerdo do tabuleiro
    	printf("%c%c%c",196,196,196); //caractere central(-)
    	if(j==N-1) printf("%c\n",180); //canto direito
		if(j!=N-1  )printf("%c",197); //caractere central seguinte
	}
}

void linha_meio_final(void){
	for(int j=0;j<N;j++) {
    	if(j==0) printf("%c",192); //canto superior esquerdo do tabuleiro
    	printf("%c%c%c",196,196,196); //caractere central(-)
    	if(j==N-1) printf("%c\n",217); //canto superior direito
		if(j<N-1) if(j<N-6||j>N-3)printf("%c",193); else printf("%c",197);//caractere central seguinte
		} 
}

void linha_final(void){
	for(int j=0;j<N-4;j++) {
    	if(j==0) printf("%c",192); //canto superior esquerdo do tabuleiro
    	printf("%c%c%c",196,196,196); //caractere central(-)
    	if(j==N-5) printf("%c\n",217); //canto superior direito
		if(j!=N-5)printf("%c",193); //caractere central seguinte
		}
}


void mostra_tabul(void){
		printf("  ");for(int num=0;num<N;num++){printf(" %d  ",num+1); if(num==N-1) printf("\n");} //Substiuir por for
     	printf("         "); linha_topo(); //printf("         |---|---|---|\n");
      for(int i=0; i<N; i++) {
          
		 if(i<2) {
		 		printf("%c      ",i+65);//letras a esquerda A,B,C,D,E,F,G
		 		for(int j=0; j<3; j++){
         		if(j==0) printf("  ");//espaçamento entre linhas
         		else printf(" ");
         		printf("%c %c",179,conv(tabul[i][j])); } //barras intermedias
        		//if(i==1) printf("  |           |%c\n |---|---|---|---|---|---|---|\n",i+65);   //substituir por ciclo for
        		//if(i<1) printf("             |%c\n	 |---|---|---|\n",i+65);   				   //substituido por ciclo for	
        		printf(" %c	      %c",179,i+65);
				if(i<1)  {printf("\n         ");linha_central_topo();}
				if(i==1) {printf("\n "); linha_3();}
			
         }
         if(i>=2&&i<=4) { 
         	printf("%c",i+65);
		 		for(int j=0; j<7; j++){
         		printf("");
         		//if (j==3&&i==2) printf("  %c ",82);//desenha o R
				if(i==4) printf("%c %c ",179,71); 		//desenha os G
				else printf("%c %c ",179,conv(tabul[i][j]));
        		  }
        		if(i<3) {printf("%c%c\n",179,i+65); linha_central_meio();}
				if(i==3) {printf("%c%c\n",179,i+65); linha_central_meio(); }
				if(i>3) {printf("%c%c\n ",179,i+65); linha_meio_final(); }
         }
         if(i>4) {
         printf("%c      ",i+65);
		 		for(int j=0; j<3; j++){
		 		if(j==0) printf("  ");	
		 		else printf(" ");
        		if(i==5||i==6) printf("%c %c",179,71); //desenha os G	
        		else printf("%c%c",179, conv(tabul[i][j]));  } //barras intermedias
        		if(i==5) {printf(" %c        %c\n	 ",179,i+65);linha_central_topo();}
        		if(i==6) {printf(" %c        %c\n	 ",179,i+65); linha_final();}
				}
	}
		printf("   1   2   3   4   5   6   7");
}
int main(){
	inicia_tabul();
	mostra_tabul();
	
}
