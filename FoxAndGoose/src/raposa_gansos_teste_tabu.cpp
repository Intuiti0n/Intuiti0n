/*
Jogo Raposa e Gansos (C/C++) - versão 2 (melhor organizado e mais extensivel)
Luis Paulo Reis
baseado em C: The Complete Reference, 4th Ed. by Herbert Schildt
ISBN: 0072121246, McGraw-Hill Osborne Media; 4 edition (2000)
*/

#include <cstdio>  //input-output - necessario para scanf e printf
#include <cstdlib> //standard lib contém função PAUSE

#define N 7

short int tabul[N][N];  // tabuleiro do Jogo Raposa e Gansos com inteiros
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
  printf("Jogo Raposa e Gansos - Grupo 5 MIEEIC \n");
  mostra_tabul();
  return 0;
}


// Inicializa o Tabuleiro colocando-o todo vazio ' '
void inicia_tabul(void)
{
  int i, j;

  for(i=0; i<7; i++)
    for(j=0; j<7; j++) 
       tabul[i][j] = 0;                   
}

char conv(short int peca)
{
   if (peca==1) return 'X';    
   else if (peca==2) return 'O';    
   else return ' ';    
}

void mostra_tabul(void)
{
     printf("   1   2   3   4   5   6   7");
     printf("\n |---|---|---|---|---|---|---|\n");
     for(int i=0; i<7; i++) {
         printf("%c",i+65);    
         for(int j=0; j<7; j++)
              printf("| %c ", conv(tabul[i][j])); 
         printf("|%c\n |---|---|---|---|---|---|---|\n",i+65);
     }
     printf("   1   2   3   4   5   6   7\n\n");
}


