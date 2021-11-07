// 									Kaeru Jump
// Código adaptado por:
// Afonso Santos a73746		e		Daniel Gomes  a74729 , de
// Luis Paulo Reis, University of Minho, Portugal, lpreis@dsi.uminho.pt
// adapted From: Ben Marchant, "The Same Game: A Simple Game from Start to Finish", 2005
#include "SameGameBoard.h"
#include <stack>   //stack class!
using namespace std;


class Coordenadas{		// Class usada no undo e redo para "guardar" a posição do sapo
	public:				
	int x, y, dir;
	Coordenadas() {}
    Coordenadas(int linhas, int colunas, int direcao){
  		x = linhas;
  		y = colunas;
  		dir = direcao;
	}	
};

class CSameGame
{
public:
  CSameGame();
  ~CSameGame();
  // Functions for accessing the game board
  char GetBoardSpace(int row, int col) { return m_board->GetBoardSpace(row, col); }
  void SetupBoard(void)         { m_board->SetupBoard(); }
  int GetColumns(void)          { return m_board->GetColumns(); }
  void SetColumns(int nColumns) { m_board->SetColumns(nColumns); }
  int GetRows(void)             { return m_board->GetRows(); }
  void SetRows(int nRows)       { m_board->SetRows(nRows); }
  void DeleteBoard(void)        { m_board->DeleteBoard(); }
  bool IsLevelOver()            { return m_board->IsLevelOver(); }
  void InputGameParameters();
  void GetMove(int &row, int &col);
  void GetGraphMove(int &row, int &col);
  void DrawBoard();
  void NewGame();
  void Game();
  //Undo/Redo move, Load/Save game functions
  void UndoLast();
  bool CanUndo();
  void RedoLast();
  bool CanRedo(); 
  void GravaTabRedo();
  void GravaTabUndo();

private:
  CSameGameBoard* m_board; // Instance of the game board
  void ClearUndo();  //  Function to clear undo stack
  void ClearRedo();  //  Function to clear redo stack
  stack<Coordenadas> m_undo;    //  Undo stack
  stack<Coordenadas> m_redo;    //  Redo stack
};
