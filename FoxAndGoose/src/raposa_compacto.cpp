//Raposa e gansos Final
#include <cstdio>  //input-output - necessario para scanf e printf
#include <cstdlib> //standard lib contém função PAUSE
#include<ctype.h>
#include<time.h>
#include<math.h>
#define N 7

short int tabul[N][N];  // tabuleiro do Jogo do Galo (3x3) com inteiros
                        // 0- vazio, 1-peça jog1, 2-peça jog2
int tipo_jogo(void);
void inicia_tabul(void);
void mostra_tabul(void);
void jogada(int n, int jog, int tipo);
void jogada_Humano(int n,int jog,int tipo);
void jogada_PC(int jog, int n);
int fim_jogo(int n);
int avalia_tabul(int jog);
void finaliza(int ti, int jog, char venc);
bool movimento_valido(int xi, int yi, int xf, int yf, int jog);
bool movimento_normal(int xi, int yi, int xf, int yf, int jog);
bool movimento_comer(int xi, int yi, int xf, int yf, int jog);
bool deteta_ganso(int xi, int yi, int xf, int yf, int jog);
void executa_movimento(int xi, int yi, int xf, int yf, int jog);
void executa_movimento_comer(int xi, int yi, int xf, int yf, int jog);
void grava_jogo(int n,int jog,int tipo);
void le_jogo(int n,int jog,int tipo);
void menu();
void move_aleatorio(int xi, int yi, int xf, int yf, int jog);
void linha(int t, char c);
// Função principal (main) do jogo - contém o ciclo central do jogo

int main(void){
  int fim, n, jog, tipo;
  int xg,yg;
  printf("\n");
  menu();
  tipo = tipo_jogo();
  fim = -1; n = 0; jog = 0;
  inicia_tabul();
  do {
  	if (n==0) printf("Come%cam os gansos!\n",135);
    n++; 
    if (jog==1) jog = 2; else jog = 1;   //troca jogador
    linha(1,9);printf("Jogada No: %d %c  Jogador: %d %c  Av: %d\n", n,186, jog,186, avalia_tabul(jog));linha(1,10);
    linha(1,9);printf("Para gravar o jogo use a combina%c%co: 2 2",135,198);linha(1,10);linha(1,9);printf("Para carregar o jogo use a combina%c%co: 1 1",135,198);linha(3,10);
    mostra_tabul();                   // mostra o tabuleiro no ecran
	jogada(n, jog, tipo);
    fim = fim_jogo(n);  
  } while(fim==-1);   

  finaliza(tipo,jog,fim);
   if (fim==1) printf ("\n\tOs Gansos (Jogador 1) ganharam!!\n");
		else if(fim==2) printf("\n\tA Raposa (Jogador 2) ganhou!!\n");  
  return 0;
}

void linha(int t, char c){
	for(int i=0;i<t;i++)
			printf("%c",c);
}

void menu(){
	int a;
	char regra [80], st[80]; 
	FILE *fich;
	linha(1,9);linha(49,177);linha(1,10);
	linha(1,9);linha(1,177);linha(1,9);printf("Bem-vindo ao Jogo Raposa e Gansos");linha(1,9);linha(1,177); linha(1,10);
	linha(1,9);linha(1,177);linha(6,9);linha(1,177);linha(1,10); linha(1,9);linha(1,177);linha(6,9);linha(1,177);linha(1,10);
	linha(1,9);linha(1,177);linha(2,9);printf("1 - Ver Regras"); linha(3,9);linha(1,177);linha(1,10);
	linha(1,9);linha(1,177);linha(6,9);linha(1,177);linha(1,10);
	linha(1,9);linha(1,177);linha(2,9);printf("2 - Jogar");linha(3,9);linha(1,177);linha(1,10);    
	linha(1,9);linha(49,177);linha(2,10);
		fflush(stdin);
		a=-1; 
		gets(st);
		for(int i=0;i<80;i++){
		if(isdigit(st[i])&&a==-1) a=st[i]-48;
		}
	switch(a){
		case 1: FILE *ficheiro;
					if((ficheiro=fopen("Regras.txt","r"))==NULL){
						printf("O ficheiro n%co foi aberto\n",198); return; }
					while(!feof(ficheiro)){
						fgets(regra,80, ficheiro); printf("%s",regra); } system("PAUSE"); break;
		
		case 2: return; break;
		default: printf("Essa op%c%co n%co existe! Escolha outra.\n\n",135,198,198); menu(); 
	}
	printf("\n");
}

// Inicializa o Tabuleiro colocando-o todo vazio ' '
void inicia_tabul(void){ //inicia o tabuleiro com espaços vazios (tabul[i][j]=0) ou  G (tabul[i][j]=1) ou R(tabul[i][j]=2)
  int i, j;
  for(i=1; i<=N; i++){
  	for(j=1; j<=N; j++) {
		if(i==3&&j==4) tabul[i][j] = 2; //desenha a raposa na posição 3,4	
		else if(i==5) tabul[i][j] = 1;
		else if(i>5&&j>2&&j<6)  tabul[i][j] = 1;
		else if(i<3&&j<3 || i<3&&j>5|| i>5&&j<3 ||i>5&&j>5 ) tabul[i][j]=-1;
		else tabul[i][j]=0;
		}
	}      
}

// Pede ao utlizador que escolha um dos 4 modos de jogo possiveis
// Modos de jogo: 1-Hum/Hum 2-Hum/PC 3-PC/Hum 4-PC/PC
int tipo_jogo(void){
    int ti;
    char st[80];
    linha(2,10);linha(2,9);printf("Introduza o modo de jogo (1-4)"); linha(2,10);
    linha(1,9);linha(1,16);printf(" Modo 1: Humano vs Humano");linha(1,10);linha(1,9);linha(1,16);printf(" Modo 2: Humano vs PC");linha(1,10);
	linha(1,9);linha(1,16);printf(" Modo 3: PC vs Humano");linha(1,10);linha(1,9);linha(1,16);printf(" Modo 4: PC vs PC");linha(2,10);
    linha(2,9);linha(1,201);linha(41,205);linha(1,187);linha(1,10);
	linha(2,9);linha(1,186);printf(" O Jogador 1 joga primeiro com os Gansos ");linha(1,186);linha(1,10);
	linha(2,9); linha(1,200);linha(41,205);linha(1,188);printf("\n");
    	fflush(stdin);
		ti=-1;
		gets(st);
		for(int i=0;i<80;i++){
		if(isdigit(st[i])&&ti==-1) ti=st[i]-48;
	}
    switch(ti){
		case 1: printf ("Escolheu jogar contra outro Humano\n"); break;
		case 2: printf ("Escolheu jogar contra o PC. Jogue primeiro\n"); break;
		case 3: printf ("Escolheu jogar contra o PC. O PC joga primeiro\n"); break;
		case 4: printf ("Escolheu o modo PC vs PC\n"); break;
		default: printf ("N%co existe essa op%cao! Escolha de novo\n\n\n",198,135); tipo_jogo();
	} return ti ; printf ("\n");
}

void grava_jogo(int n,int jog,int tipo){
	printf("\nA Guardar!\n\n");
	int jogada=n;
	FILE *fich;
	fich=fopen("Estado.txt","w");
		if(fich==NULL) {printf("\nErro de gravacao!\n"); return; }
			else fprintf(fich, "%2d %2d %2d\n",n,jog,tipo);
			
		for(int i=1; i<=N; i++){
			for(int j=1; j<=N; j++)
				fprintf(fich, "%2d ", tabul[i][j]);
			fprintf(fich, "\n");
		}
		jogada--;n=jogada; if (jog==1) jog==2; else jog=1;
		fclose(fich);
}

void le_jogo(int n,int jog,int tipo){
	printf("\nA Ler!\n\n");
	FILE *fich;
	fich=fopen("Estado.txt","r");
		if(fich==NULL) {printf("\nErro de leitura!\n"); return; }
			else fscanf(fich, "%d %d %d",&n,&jog,&tipo);
			
		for(int i=1; i<=N; i++){
			for(int j=1; j<=N; j++)
				fscanf(fich, "%d ", &tabul[i][j]);
				}
		n--; if (jog==1) jog==2; else jog=1;
		fclose(fich);
}

// Finaliza o jogo indicando quem venceu ou se foi empate
void finaliza(int ti, int jog, char venc){
     if (venc==0) printf("Empate!!!\n");
     else if (venc==1 && ti<3 || venc==2 && (ti==1 || ti==3)) 
        printf("Humano (Jogador: %d) Venceu!!!\n", jog);
        else printf("A Maquina (Jogador: %d ) Venceu!!!\n", jog);
     mostra_tabul();
}

// Dependendo do modo de jogo e do numero da jogada
// pede uma jogada ao humano ou calcula uma jogada para o PC
void jogada(int n, int jog, int tipo){
     if (n % 2 == 1) { if(tipo<=2) jogada_Humano(n,jog,tipo); else jogada_PC(jog,n);}
     else { if (tipo==1 || tipo==3) jogada_Humano(n,jog,tipo); else jogada_PC(jog,n); } 
}

// Jogada do Humano - Pede coordenadas e verifica se são validas
// e se a casa está vazia. Nesse caso coloca lá a peça respectiva
void jogada_Humano(int n,int jog,int tipo){
   int a,b,c,d;
    char st[80];
    do {  
        printf("Escolha a pe%ca que quer mover:",135);
		fflush(stdin); a=-1; b=-1; gets(st);
		for(int i=0;i<80;i++){
			if(isdigit(st[i])&&a==-1) a=st[i]-48;
			else if (isdigit(st[i])&&b==-1) b=st[i]-48;} 
	if (a==1&&b==1)  { le_jogo(tipo,n,jog); return;  }; 
	if (a==2&&b==2)  { grava_jogo(tipo,n,jog); return;  }; 
		printf("Entre a linha (1-7) e a coluna (1-7) onde quer jogar:\n");
		fflush(stdin); c=-1; d=-1; gets(st);
		for(int i=0;i<80;i++){
			if(isdigit(st[i])&&c==-1) c=st[i]-48;
			else if (isdigit(st[i])&&d==-1) d=st[i]-48;
		}
	if (c==1&&d==1)  { le_jogo(tipo,n,jog); return;  }; 
	if (c==2&&d==2)  { grava_jogo(tipo,n,jog); return;  }; 
	//xi=a; yi=b; xf=c;yf=d;
		if(tabul[a][b]!=jog) printf("Seleccionou a pe%ca errada\n",135);
        if(!movimento_valido(a,b,c,d,jog))
           printf("Jogada Inv%clida, tente novamente.\n",160);
        if(!movimento_normal(a,b,c,d,jog))
			printf("Movimento Inv%clido. So se pode mover 1 casa nessa direc%c%co\n",160,135,198); 
    } while (!(movimento_valido(a,b,c,d,jog)&&movimento_normal(a,b,c,d,jog)));
	if(jog==1) executa_movimento(a,b,c,d,jog);
    if(jog==2) {
    	if(!movimento_comer(a,b,c,d,jog)) executa_movimento(a,b,c,d,jog);
    	else if (movimento_comer(a,b,c,d,jog)&&deteta_ganso(a,b,c,d,jog)) executa_movimento_comer(a,b,c,d,jog);
    	else if (movimento_comer(a,b,c,d,jog)&& !deteta_ganso(a,b,c,d,jog)) {printf("N%co existe ganso para comer\n",198);jogada_Humano(n,2,tipo);}
    }
}

bool dentro(int x, int y){
    if(x<1||x>N||y<1||y>N||tabul[x][y]==-1) return false;
    return true;   
}

bool movimento_valido(int xi, int yi, int xf, int yf, int jog){
     if (dentro(xi,yi) && dentro(xf,yf) && tabul[xi][yi]==jog && tabul[xf][yf]==0)
        return true;
     return false; 
}

bool movimento_normal(int xi, int yi, int xf, int yf, int jog){
	if((abs(xf-xi)==1)&&(yf==yi)) return true;
	if((abs(yf-yi)==1)&&(xf==xi)) return true;
	if(jog==2) {
		if((abs(xf-xi)==1)&&(abs(yf-yi)==1)) return true;
		if((abs(xf-xi)==2)&&((yf==yi)||(abs(yf-yi)==2))) return true;
		if((abs(yf-yi)==2)&&((xf==xi)||(abs(xf-xi)==2))) return true;
	}
	return false;
}

bool movimento_comer(int xi, int yi, int xf, int yf, int jog){	
	if(abs(xf-xi)==2||abs(yf-yi)==2) return true;
	if(abs(xf-xi)==1||abs(yf-yi)==1) return false;
	return false;
}

bool deteta_ganso(int xi, int yi, int xf, int yf, int jog){
	if(tabul[(xf+xi)/2][(yf+yi)/2]==1) return true;
	return false;
}

bool deteta_rodeado(){ //jogador 2 
	int xi,yi;
	for(int i=1; i<=N; i++)	
	for(int j=1; j<=N; j++)
		if(tabul[i][j]==2) {xi=i;yi=j;}
		int w=0;
	if(dentro(xi-1,yi)) {if(tabul[xi-1][yi]==1) w++;if(tabul[xi-2][yi]==1) w++;}		
	if(!dentro(xi-1,yi)) w++;
	
	if(dentro(xi-1,yi-1)) {if (tabul[xi-1][yi-1]==1) w++;if (tabul[xi-2][yi-2]==1) w++;}
	if(!dentro(xi-1,yi-1)) w++;
	
	if(dentro(xi-1,yi+1)) {if(tabul[xi-1][yi+1]==1) w++;if(tabul[xi-2][yi+2]==1) w++;}
	if(!dentro(xi-1,yi+1)) w++;
	
	if(dentro(xi,yi-1)) {if(tabul[xi][yi-1]==1) w++;if(tabul[xi][yi-2]==1) w++;	}
	if(!dentro(xi,yi-1)) w++;
	
	if(dentro(xi,yi+1)) {if(tabul[xi][yi+1]==1) w++;if(tabul[xi][yi+2]==1) w++;}
	if(!dentro(xi,yi+1)) w++;
	
	if(dentro(xi+1,yi-1)) {if(tabul[xi+1][yi-1]==1) w++;if(tabul[xi+2][yi-2]==1) w++;}
	if(!dentro(xi+1,yi-1)) w++;
	
	if(dentro(xi+1,yi)) {if(tabul[xi+1][yi]==1) w++;if(tabul[xi+2][yi]==1) w++;	}
	if (!dentro(xi+1,yi)) w++;
	
	if(dentro(xi+1,yi+1)) {if(tabul[xi+1][yi+1]==1) w++;if(tabul[xi+2][yi+2]==1) w++;}
	if(!dentro(xi+1,yi+1)) w++;
	
	if(w==11) return true;
	else return false;
}
void executa_movimento(int xi, int yi, int xf, int yf, int jog)
{
      tabul[xi][yi] = 0;    
      tabul[xf][yf] = jog;
}

void executa_movimento_comer(int xi, int yi, int xf, int yf, int jog){
	tabul[xi][yi] = 0;
	tabul[xf][yf] = jog;	    
	tabul[(xf+xi)/2][(yf+yi)/2]=0; //coordenadas do ganso a ser eliminado
}

// Movimento do Computador - Joga no meio ou canto (2,2) nas duas primeiras jogadas
// nas restantes procura maximizar a avaliação do tabuleiro (linhas e ameaças
// de linha
void move_aleatorio(int xi, int yi, int xf, int yf, int jog){
	srand(time (NULL));
	int dirx, diry,dir1,dir2;
	do{
	if(jog==1){ //jogador 1 apenas se move
	int linha=1+(rand()%7);
	int coluna= 1+(rand()%7);
	xi=linha; yi=coluna;
	dir1 = rand()%4;    //Sorteia uma de 4 possiveis direções (0, 1, 2 ou 3)
	switch (dir1){
		case 0: dirx=1; diry=0; break;  //Direção 0: direita move uma casa no eixo dos xx
		case 1: dirx=0; diry=1; break;  //baixo
		case 2: dirx=-1; diry=0; break; //Direção 2: esquerda move uma casa para trás no exio dos xx
		case 3: dirx=0; diry=-1; break; //cima
	}
	xf=xi+dirx;
	yf=yi+diry;
	}
	
	if(jog==2){ //jogador 2 come se tiver um ganso enconstado, senão move-se aleatoriamente
	for(int i=1; i<=N; i++)	
	for(int j=1; j<=N; j++)
		if(tabul[i][j]==2) {xi=i;yi=j;}
		//condições para comer gansos se se encontrarem enconstados à raposa
			 if((tabul[xi-1][yi-1]==1)&&movimento_valido(xi,yi,xi-2,yi-2,jog)&&deteta_ganso(xi,yi,xi-2,yi-2,jog)) 
			 {executa_movimento_comer(xi,yi,xi-2,yi-2,jog); return;}
		else if((tabul[xi-1][yi]==1)  &&movimento_valido(xi,yi,xi-2,yi,jog)&&deteta_ganso(xi,yi,xi-2,yi,jog))  
			 {executa_movimento_comer(xi,yi,xi-2,yi,jog);return;}
		else if((tabul[xi-1][yi+1]==1)&&movimento_valido(xi,yi,xi-2,yi+2,jog)&&deteta_ganso(xi,yi,xi-2,yi+2,jog))
		     {executa_movimento_comer(xi,yi,xi-2,yi+2,jog); return;}
		else if((tabul[xi][yi-1]==1)  &&movimento_valido(xi,yi,xi,yi-2,jog)&&deteta_ganso(xi,yi,xi,yi-2,jog))  
		 	 {executa_movimento_comer(xi,yi,xi,yi-2,jog);return;}
		else if((tabul[xi][yi+1]==1)  &&movimento_valido(xi,yi,xi,yi+2,jog)&&deteta_ganso(xi,yi,xi,yi+2,jog))  
		 	 {executa_movimento_comer(xi,yi,xi,yi+2,jog);return;}
		else if((tabul[xi+1][yi-1]==1)&&movimento_valido(xi,yi,xi+2,yi-2,jog)&&deteta_ganso(xi,yi,xi+2,yi-2,jog)) 
			 {executa_movimento_comer(xi,yi,xi+2,yi-2,jog);return;}
		else if((tabul[xi+1][yi]==1)  &&movimento_valido(xi,yi,xi-2,yi,jog)&&deteta_ganso(xi,yi,xi-2,yi,jog)) 
		     {executa_movimento_comer(xi,yi,xi-2,yi,jog);return;}
		else if((tabul[xi+1][yi+1]==1)&&movimento_valido(xi,yi,xi+2,yi+2,jog)&&deteta_ganso(xi,yi,xi+2,yi+2,jog)) 
			 {executa_movimento_comer(xi,yi,xi+2,yi+2,jog);return;}
		else{//condiçoes para se mover aleatoriamente
			 dir2 = rand()%8;
	switch (dir2){
		case 0: dirx=1;  diry=0;  break;  //Direção 0: direita move uma casa no eixo dos xx
		case 1: dirx=0;  diry=1;  break;  //baixo
		case 2: dirx=-1; diry=0;  break; //Direção 2: esquerda move uma casa para trás no exio dos xx
		case 3: dirx=0;  diry=-1; break; //cima
		case 4: dirx=-1; diry=1;  break; //diagonal para cima à direita
		case 5:	dirx=-1; diry=-1; break; //diagonal para cima à esquerda
		case 6:	dirx=1;  diry=-1; break; //diagonal para baixo à esquerda
		case 7:	dirx=1;  diry=1;  break; //diagonal para baixo à direita 
		}
	xf=xi+dirx;
	yf=yi+diry;
	}}
	}while(!movimento_valido(xi,yi,xf,yf,jog));
	executa_movimento(xi,yi,xf,yf,jog);
}

void jogada_PC(int jog, int n){
	int xi,yi,xf,yf;
	move_aleatorio(xi,yi,xf,yf,jog);
	return;
}

char conv(short int peca){
   if (peca==1) return 'G';   //jogador 1 começa com os gansos 
   else if (peca==2) return 'R';    
   else if(peca==0) return ' ';//casa vazia
   else if(peca==-1) return ' ';//casa fora do tabuleiro    
}

// Mostrar o Tabuleiro no Ecran com aspecto semelhante ao tabuleiro
void linha_topo(void){ //1ª linha do tabuleiro, por baixo dos numeros
	printf("%c",218); //canto superior esquerdo do tabuleiro
	for(int j=1;j<N-3;j++) {
    	printf("%c%c%c",196,196,196); //caractere central(---) 
		if(j!=N-4)printf("%c",194); //caractere central seguinte "T"
		}printf("%c\n",191);} //canto superior direito do tabuleiro
void linha_3(void){ 			 //desenha a linha que separa as peças que estao na linha 2 das da linha 3. 
		printf("%c",218); //canto esquerdo da linha
		for(int j=1;j<=N;j++) { 
    	printf("%c%c%c",196,196,196); //caractere central(---)
		if(j<N) if(j<N-5||j>N-2)printf("%c",194); else printf("%c",197);//caractere central seguinte (194= "T" ; 197= "+")
		} printf("%c\n",191);}//canto direito da linha

void linha_central_topo(void){ //desenha |---|---|---| com caracteres ASCII
	printf("%c",195); //canto esquerdo (|-)
	for(int j=1;j<N-3;j++) {
    	printf("%c%c%c",196,196,196); //caractere central(---)
		if(j!=N-4)printf("%c",197); //caractere central seguinte (+)
		} printf("%c\n",180);} //canto direito (-|)

void linha_central_meio(void){ //desenha |---|---|---|---|---|---|---| com caracteres ASCII
	printf(" "); printf("%c",195); //canto esquerdo (|-)
	for(int j=1;j<=N;j++){ 
    	printf("%c%c%c",196,196,196); //caractere central(---)
		if(j!=N)printf("%c",197); //caractere central seguinte (+)
	}printf("%c\n",180);} //canto direito (-|)

void linha_meio_final(void){ //traço que separa a linha 5 da linha 6
	printf("%c",192); //canto inferior esquerdo  |_
	for(int j=1;j<=N;j++) {
    	printf("%c%c%c",196,196,196); //caractere central(---)
		if(j<N) if(j<N-5||j>N-2)printf("%c",193); else printf("%c",197);//caractere central seguinte (193= "_|_"; 197= "+")
		} printf("%c\n",217);} //canto inferior direito   _|

void linha_final(void){ //ultima linha do tabuleiro
	printf("%c",192); //canto inferior esquerdo do tabuleiro
	for(int j=1;j<N-3;j++) {
    	printf("%c%c%c",196,196,196); //caractere central(---)
		if(j!=N-4)printf("%c",193); //caractere central seguinte "T" invertido
		} printf("%c\n",217);} //canto inferior direito do tabuleiro

void mostra_tabul(void){
	printf("  ");for(int num=0;num<N;num++){printf(" %d  ",num+1); if(num==N-1) printf("\n");} //Imprime os numeros de 1 ate N(N=7 neste caso) por cima do tabuleiro
     	printf("         "); linha_topo(); //Desenha a 1ª linha do tabuleiro. ("         |---|---|---|\n");
	for(int i=1; i<=N; i++) {
		 if(i<3) {
		 		printf("%d",i);//numeros a esquerda 1,2,3,4,5,6,7
		 		for(int j=1; j<=N; j++){ 
		 		if(j<N-4) printf("%c %c ",0,conv(tabul[i][j]));
         		if(j>=N-4&&j<N)printf("%c %c ",179,conv(tabul[i][j]));  //desenha as barras verticais e adiciona uma posição da matriz 
         		if(j>N-1) printf("%c %c ",0,conv(tabul[i][j]));}
        		printf(" %d",i); //desenha a ultima barra da linha e o numero à direita do tabuleiro
				if(i<N-5)  {printf("\n         ");linha_central_topo();} //desenha |---|---|---|
				if(i==N-5) {printf("\n "); linha_3();} //muda de linha porque o traço que separa a linha 2 da linha 3 é diferente dos restantes
         }
         if(i>=N-4&&i<=N-2) { 
         	printf("%d",i);//desenha numero a esquerda do tabuleiro
		 		for(int j=1; j<=N; j++) {printf("%c %c ",179,conv(tabul[i][j]));}//desenha as barras verticais(|) e adiciona posiçoes da matriz
        		if(i<=N-3) {printf("%c%d\n",179,i); linha_central_meio();} //desenha a ultima barra vertical da linha, o nº à direita e o traço da linha seguinte
				if(i>N-3) {printf("%c%d\n ",179,i); linha_meio_final(); }//desenha o ultimo traço do meio do tabuleiro |___|___+___+___+___+___|___|
         }
         if(i>N-2) {
         printf("%d",i); //desenha numero a esquerda do tabuleiro
		 		for(int j=1; j<=N; j++){
		 	if(j<N-4) printf("%c %c ",0,conv(tabul[i][j]));
         		if(j>=N-4&&j<=N-1)printf("%c %c ",179,conv(tabul[i][j]));  //desenha as barras verticais e adiciona uma posição da matriz 
         		if(j>N-1) printf("%c %c ",0,conv(tabul[i][j]));}
        		if(i==N-1) {printf(" %d\n	 ",i);linha_central_topo();} //desenha a ultima barra vertical e o traço da linha seguinte
        		if(i==N) {printf(" %d\n	 ",i); linha_final();}//desenha a ultima barra da linha e o ultimo traço do tabuleiro-> |___|___|___|
				}
	}printf("  ");
		for(int num=0;num<N;num++){printf(" %d  ",num+1); if(num==N-1) printf("\n");} //Imprime os numeros de 1 ate N por baixo do tabuleiro
}
// Verificar se o jogo terminou retornando o simbolo do jogador que
// ganhou, 'E' em caso de empate ou ' ' em caso de nao ter acabado
int fim_jogo(int n){
	int xf,yf;
	int w;
	int contador=0,jog,xi,yi;
		for(int i=1; i<=N; i++)
			 for(int j=1; j<=N; j++)
				 if (tabul[i][j]==1) contador++; 
				 
		 if (contador<=5) return 2;  // Se tiver 5 ou menos peças 1 (gansos), a raposa ganha 	

			for(int i=1; i<=N; i++)
				for(int j=1; j<=N; j++)// O x da posiçao da raposa passa para o xr e o y passa para o yr
					 if (tabul[i][j]==2){xi=i;yi=j;} //procura a raposa
					if(deteta_rodeado()) return 1;
	return -1;	
//		 else if(movimento_valido(a,b,c,d,2)!= true && movimento_normal(a,b,c,d,2)!= true && movimento_comer(a,b,c,d,2)!= true)  return 1; // A raposa nao se consegue mexer. Os gansos ganham
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
