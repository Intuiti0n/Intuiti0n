/*
Jogo do Galo (C/C++) - versão 2 (melhor organizado e mais extensivel)
Luis Paulo Reis
baseado em C: The Complete Reference, 4th Ed. by Herbert Schildt
ISBN: 0072121246, McGraw-Hill Osborne Media; 4 edition (2000)
*/

#include <cstdio>  //input-output - necessario para scanf e printf
#include <cstdlib> //standard lib contém função PAUSE

#define N 7

short int tabul[N][N];  // tabuleiro do Jogo do Galo (3x3) com inteiros
                        // 0- vazio, 1-peça jog1, 2-peça jog2
int tipo_jogo(void);
void inicia_tabul(void);
void mostra_tabul(void);
void jogada(int n, int jog, int tipo);
void jogada_Humano(int jog);
void jogada_PC(int jog, int n);
int fim_jogo(int n);
int avalia_tabul(int jog);
void finaliza(int ti, int jog, char venc);
bool movimento_valido(int x, int j, int jog);
void executa_movimento(int x, int y, int jog);

// Função principal (main) do jogo - contém o ciclo central do jogo
int main(void)
{
  int fim, n, jog, tipo;

  printf("Jogo do Galo - MIEEIC Humano vs PC\n");
  tipo = tipo_jogo();
  fim = -1; n = 0; jog = 0;
  inicia_tabul();

  do {
    n++; 
    if (jog==1) jog = 2; else jog = 1;   //troca jogador
    printf("Jogada No: %d  Jogador: %d  - Av: %d\n", n, jog, avalia_tabul(jog));
    mostra_tabul();                   // mostra o tabuleiro no ecran
    jogada(n, jog, tipo);             
    fim = fim_jogo(n);  
  } while(fim==-1);   

  finaliza(tipo,jog,fim);
  
  system("PAUSE");
  return 0;
}

// Inicializa o Tabuleiro colocando-o todo vazio ' '
void inicia_tabul(void)
{
   int i, j;

  for(i=1; i<N+1; i++){
  	for(j=0; j<N+1; j++) {
    	/*if(i==3&&j==4)  tabul[i][j] = 1;         
    	if(i>=5) tabul[i][j] = 2; 
    	if(i==1&&j==3)  tabul[i][j] = 2;}*/
         tabul[i][j] = 0;}
		}      
}

// Pede ao utlizador que escolha um dos 4 modos de jogo possiveis
// Modos de jogo: 1-Hum/Hum 2-Hum/PC 3-PC/Hum 4-PC/PC
int tipo_jogo(void)
{
    int ti;
    printf("Escolha um modo de jogo: \n");
    printf("1-Hum/Hum 2-Hum/PC 3-PC/Hum 4-PC/PC\n"); 
    scanf("%d",&ti);
    return ti;
}


// Finaliza o jogo indicando quem venceu ou se foi empate
void finaliza(int ti, int jog, char venc)
{
     if (venc==0) printf("Empate!!!\n");
     else if (venc==1 && ti<3 || venc==2 && (ti==1 || ti==3)) 
        printf("Humano (Jogador: %d) Venceu!!!\n", jog);
        else printf("A Maquina (Jogador: %d ) Venceu!!!\n", jog);
     mostra_tabul();
}


// Dependendo do modo de jogo e do numero da jogada
// pede uma jogada ao humano ou calcula uma jogada para o PC
void jogada(int n, int jog, int tipo)
{
     if (n % 2 == 1) {
           if (tipo<=2) jogada_Humano(jog); else jogada_PC(jog,n);
     }
     else { 
          if (tipo==1 || tipo==3) jogada_Humano(jog); else jogada_PC(jog,n);
     }
}


// Jogada do Humano - Pede coordenadas e verifica se são validas
// e se a casa está vazia. Nesse caso coloca lá a peça respectiva
void jogada_Humano(int jog)
{
    int x, y;

    do {
        printf("Entre a linha (1-3) e a coluna (1-3) onde quer jogar: ");
        scanf("%d%*c%d", &x, &y);
        x--; y--;

        if(!movimento_valido(x,y,jog))
           printf("Jogada Invalida, tente novamente.\n");
    } while (!movimento_valido(x,y,jog));
    executa_movimento(x,y,jog);
}


bool movimento_valido(int x, int y, int jog)
{
     if(x<0 || x>2 || y<0 || y>2 || tabul[x][y]!= 0) return false;
     return true;  
}


bool dentro(int x, int y)
{
    if(x<0 || x>N-1 || y<0 || y>N-1) return false;
    return true;   
}

// Exemplo de Movimento Valido de jogada de um ponto para outro ponto
/*
bool movimento2_valido(int xi, int yi, int xf, int yf, int jog)
{
     if (dentro(xi,yi) && dentro(xf,yf) && tab[xi][yi]==jog && tab[xf][yf]==0)
        return true;
     return false; 
}*/
void executa_movimento(int x, int y, int jog)
{
      tabul[x][y] = jog;    
}
// Exemplo de execucao de um movimento de um ponto para outro
/*
void executa_movimento2(int xi, int yi, int xf, int yf, int jog)
{
      tabul[xi][yi] = 0;    
      tabul[xf][yf] = jog;
}*/

// Movimento do Computador - Joga no meio ou canto (2,2) nas duas primeiras jogadas
// nas restantes procura maximizar a avaliação do tabuleiro (linhas e ameaças
// de linha
void jogada_PC(int jog, int n)
{
  int i, j, bi, bj, av, maxav=-1000;
  
  if (n==1 || n==2 && movimento_valido(1,1,jog)) 
  	{ executa_movimento(1,1,jog); return; }
  if (n==2 && movimento_valido(2,2,jog)) 
  	{ executa_movimento(2,2,jog); return; }
  
  for(i=0; i<3; i++)
     for(j=0; j<3; j++) {
        if (movimento_valido(i,j,jog)) {
           tabul[i][j] = jog; //executa jogada
           av = avalia_tabul(jog);
           if (av>maxav) { maxav = av;  bi = i; bj = j; }
           tabul[i][j] = 0;   //desfaz jogada
        }
     }
  executa_movimento(bi,bj,jog); 
  return;
}

char conv(short int peca)
{
   if (peca==1) return 'R';    
   else if (peca==2) return 'G';    
   else return ' ';    
}

// Mostrar o Tabuleiro no Ecran com aspecto semelhante ao tabuleiro
// original do jogo do galo. Melhorar...
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

void mostra_tabul(void)
{
    	printf("  ");for(int num=0;num<N;num++){printf(" %d  ",num+1); if(num==N-1) printf("\n");} //Substiuir por for
     	printf("         "); linha_topo(); //printf("         |---|---|---|\n");
      for(int i=0; i<N; i++) {
          
		 if(i<2) {
		 		printf("%c      ",i+65);//letras a esquerda A,B,C,D,E,F,G
		 		for(int j=N-4; j<N-1; j++){
         		if(j==0) printf("  ");//espaçamento entre linhas
         		else printf(" ");
         		printf("%c %c",179,conv(tabul[i][j])); } //barras intermedias
        		printf(" %c	      %c",179,i+65);
				if(i<1)  {printf("\n         ");linha_central_topo();}
				if(i==1) {printf("\n "); linha_3();}
         }
         if(i>=2&&i<=4) { 
         	printf("%c",i+65);
		 		for(int j=0; j<7; j++) {printf("%c %c ",179,conv(tabul[i][j]));}
        		if(i<3) {printf("%c%c\n",179,i+65); linha_central_meio();}
				if(i==3) {printf("%c%c\n",179,i+65); linha_central_meio(); }
				if(i>3) {printf("%c%c\n ",179,i+65); linha_meio_final(); }
         }
         if(i>4) {
         printf("%c      ",i+65);
		 		for(int j=0; j<3; j++){
		 		if(j==0) printf("  ");	
		 		else printf(" ");
        		//if(i==5||i==6) printf("%c %c",179,71); //desenha os G	
        		printf("%c %c",179, conv(tabul[i][j]));  } //barras intermedias
        		if(i==5) {printf(" %c        %c\n	 ",179,i+65);linha_central_topo();}
        		if(i==6) {printf(" %c        %c\n	 ",179,i+65); linha_final();}
				}
	}
		printf("   1   2   3   4   5   6   7\n");
}

// Verificar se o jogo terminou retornando o simbolo do jogador que
// ganhou, 'E' em caso de empate ou ' ' em caso de nao ter acabado
int fim_jogo(int n)
{
  int i;

  for(i=0; i<3; i++) // testar as linhas
    if(tabul[i][0]==tabul[i][1] && tabul[i][0]==tabul[i][2] && tabul[i][0]!=0) 
       return tabul[i][0];

  for(i=0; i<3; i++) // testar as colunas
    if(tabul[0][i]==tabul[1][i] && tabul[0][i]==tabul[2][i] && tabul[0][i]!=0) 
       return tabul[0][i];

  // testar as diagonais
  if(tabul[0][0]==tabul[1][1] && tabul[1][1]==tabul[2][2] && tabul[0][0]!=0) 
     return tabul[0][0];
  if(tabul[0][2]==tabul[1][1] && tabul[1][1]==tabul[2][0] && tabul[0][2]!=0) 
     return tabul[0][2];

  if (n==9) return 0; //Acabou com empate
  
  return -1; //Ainda não acabou
}


// calcula as ameaças de linha (2 peças em linha) para um dado jogador
int avalia(int jog)
{
    int i;
    int av = 0;
    
    if (fim_jogo(0) == jog) av+=100; 
    
    for (i=0; i<3; i++) { 
       if(tabul[i][0]==jog && tabul[i][1]==jog && tabul[i][2]==0) av++;
       if(tabul[i][0]==jog && tabul[i][2]==jog && tabul[i][1]==0) av++;
       if(tabul[i][1]==jog && tabul[i][2]==jog && tabul[i][0]==0) av++;
    }
    for (i=0; i<3; i++) {
       if(tabul[0][i]==jog && tabul[1][i]==jog && tabul[2][i]==0) av++;
       if(tabul[0][i]==jog && tabul[2][i]==jog && tabul[1][i]==0) av++;
       if(tabul[1][i]==jog && tabul[2][i]==jog && tabul[0][i]==0) av++;
    }
    if(tabul[0][0]==jog && tabul[1][1]==jog && tabul[2][2]==0) av++;
    if(tabul[0][0]==jog && tabul[2][2]==jog && tabul[1][1]==0) av++;
    if(tabul[1][1]==jog && tabul[2][2]==jog && tabul[0][0]==0) av++;
    if(tabul[0][2]==jog && tabul[1][1]==jog && tabul[2][0]==0) av++;
    if(tabul[0][2]==jog && tabul[2][0]==jog && tabul[1][1]==0) av++;
    if(tabul[1][1]==jog && tabul[2][0]==jog && tabul[0][2]==0) av++;
    return av;    
}


// Avalia o tabuleiro dando um valor 0 se estiver equilibrado, positivo
// se o jogador 1 tiver mais ameaças de linha ou negativo caso contrario
int avalia_tabul(int jog)
{
    int a1, a2;
    a1 = avalia(1);
    a2 = avalia(2);
    if (jog==1) return 2*a1-3*a2; else return 2*a2-3*a1;  
}


