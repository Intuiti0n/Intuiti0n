// 									Kaeru Jump
// Código adaptado por:
// Afonso Santos a73746		e		Daniel Gomes  a74729 , de
// Luis Paulo Reis, University of Minho, Portugal, lpreis@dsi.uminho.pt
// adapted From: Ben Marchant, "The Same Game: A Simple Game from Start to Finish", 2005

// SameGameBoard.h : interface of the CSameGameBoard class
#define GRAPH true
#include "graphics.h"  //biblioteca gráfica - WinBGI
#define SBO 600     //Tamanho da janela gráfica

//struct movimento{ int x,y; };

class CSameGameBoard
{
public:
  CSameGameBoard(void);   // Default Constructor
  CSameGameBoard(const CSameGameBoard& board);  //  Copy Constructor 
  ~CSameGameBoard(void);  //  Destructor
  void SetupBoard(void);  // Function to randomly setup the board
  int GetBoardSpace(int row, int col); // Get the color at row,col
  //  Accessor functions to get/set board size information 
  int GetColumns(void) const { return m_nColumns; }
  int GetRows(void) const { return m_nRows; }
  void SetColumns(int nColumns)  { m_nColumns = (nColumns >= 5) ? nColumns : 5; }
  void SetRows(int nRows)  { m_nRows = (nRows >= 5) ? nRows : 5; }
  void DeleteBoard(void);   //  Function to delete the board and free memory
  int deteta_tecla(void);
  int executa_movimento(int T, int D);
  bool IsGameOver(void) ; 	 //  Is the game over?
  bool IsLevelOver(void);
  void DrawBoard(void);
  bool ValidMove(int T, int D);    // Function to see if a move is valid
  void DrawGraphBoard(void);    // Mostra o tabuleiro em modo grafico
  int DirecaoSapo(void);  //Diz-nos para onde está virado o sapo
  int EncontraSapo(void);
  int T;	//Variavel que armazena a tecla clicada
  int D;	// Variavel que armazena a direçao do sapo
  int level;
  int tentativas;
  int pausa;
  void Hint(void);
  void Save();
  void Load();
  void FimNivel();
  int FimJogo();
  void menu();
  void Regras();		//Função para mostrar as regras
  void Controlos();		//Função para mostrar os controlos
  void Opcoes();		
  void Pausa();			//Menu pausa
  int Recorde();		//Função que deteta se existe recorde
  int old_recorde;  //Recorde que está no ficheiro
  void SetBoard (int linhas, int colunas, int direcao);
  int GetBoard (int row, int col) {return m_arrBoard[row][col]; }
  int Direita();		//Funções auxiliares do executa_movimento
  int Esquerda();
  int Cima();
  int Baixo();			
  int m_hint[9][9];		//Matriz que tem a solução
  void CarregaHint();	//Carrega o ficheiro com a solução para a matriz m_hint
  int m_nmoves; 		//Variável que conta os movimentos
  int DrawHint=1; 		//Variável usada nas opções para saber se desenha o hint
  int DrawValid=1;		//Variável usada nas opções para saber se desenha as jogadas validas
  int DoUndoRedo=1;		//Variável usada nas opções para saber se faz undo e redo
  int DrawEyes=1;		//Variável usada nas opções para saber se desenha os olhos
  int Auto_Save=0;		//Variável usada nas opções para saber se faz auto_save (inicia desativada)
 private:
  void CreateBoard(void); //Function to create the board and allocate memory
// Class Data
  int** m_arrBoard; // 2D array pointer
  //  Board size information
  char m_arrChars[10];
  int m_nColumns;
  int m_nRows;
};
