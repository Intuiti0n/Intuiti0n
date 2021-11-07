// 									Kaeru Jump
// Código adaptado por:
// Afonso Santos a73746		e		Daniel Gomes  a74729 , de
// Luis Paulo Reis, University of Minho, Portugal, lpreis@dsi.uminho.pt
// adapted From: Ben Marchant, "The Same Game: A Simple Game from Start to Finish", 2005

#include <iostream>
#include "SameGame.h"
#include <cstdlib>
#include <fstream>
#include <stack>

using namespace std;

// CSameGame construction
CSameGame::CSameGame()
{
  m_board->m_nmoves = 0;
  m_board = new CSameGameBoard(); //  There should always be a game board
  m_board->tentativas = 1; 
}

// CSameGame destruction
CSameGame::~CSameGame()
{
  delete m_board;    // Delete the current game board
  ClearUndo();    // Delete everything from the undo stack
  ClearRedo();    // Delete everything from the redo stack
}

void CSameGame::NewGame()
{
  m_board->SetupBoard();     // Set (or reset) the game board
  m_board->m_nmoves = 0;	//O contador de movimentos começa a 0
  ClearUndo();            // Clear the undo stack
  ClearRedo();            // Clear the redo stack
}

//Simple Input. Suggestion: Add Menu to control game parameters
void CSameGame::InputGameParameters()
{  
   SetColumns(9);  //matriz 9x9
   SetRows(9); 
}

// Simple Game for Human Player
void CSameGame::Game()
{
  int x, y; 
  InputGameParameters();
  NewGame();
  m_board->menu();
  while(!m_board->IsGameOver()) {
  	int L=0, U=0;  
  	while(!IsLevelOver()) {
	  if(U==0)  {GravaTabUndo();U++;}		//Grava o sapo no undo antes de se fazer um movimento	  
  	  m_board->CarregaHint();	
	  int T= m_board->deteta_tecla();
      int D= m_board->DirecaoSapo();
	  int M= m_board->executa_movimento(T,D);
	  if(T==6)  { m_board->SetupBoard();m_board->m_nmoves=0; m_board->tentativas++; ClearUndo(); ClearRedo();GravaTabUndo();}// Se carregar no ENTER faz reset ao nível e põe o contador de movimentos a 0
      if(T==7)  { L=0; m_board->level=0; m_board->tentativas=1; NewGame();GravaTabUndo(); }	// Se carregar no BACKSPACE faz reset ao jogo 
	  if(T==8)  m_board->Save();				//SaveGame
	  if(T==10) {if(m_board->DoUndoRedo==1) {m_board->m_nmoves++;RedoLast();}}					//redo
	  if(T==11) {if(m_board->m_nmoves>0&&m_board->DoUndoRedo==1) {m_board->m_nmoves--;UndoLast();}}		//undo
	  if(T==12) m_board->Pausa();				//Menu Pausa
	  if(T==13) if(m_board->DrawHint==1) m_board->Hint();	//Hint
	  if(L==0)  {if(T==9) { L=1; m_board->tentativas++;ClearUndo(); ClearRedo(); m_board->Load();GravaTabUndo();}}	//Só é permitido um LoadGame por nível
	  if(M==1)  { m_board->m_nmoves++;GravaTabUndo();} 		// Se uma jogada for executada, o contador de movimentos é incrementado
      system ("CLS");
      DrawBoard(); 
	  }
  L=0;U=0;m_board->tentativas=1; SetupBoard(); DrawBoard(); ClearUndo(); ClearRedo();m_board->m_nmoves=0; // Quando passa o nível as tentativas ficam igual a 1
  if(m_board->Auto_Save==1) m_board->Save();	//Auto Save
  }  Game();
}


void CSameGame::DrawBoard()              
{ 
     cout << "Moves: " << m_board->m_nmoves << endl; 
     cout << "Tentativas: " << m_board->tentativas << endl;  
     cout << "Nivel: " << m_board->level+1 << endl;
	 m_board->DrawBoard(); 
}

void CSameGame::GravaTabRedo()
{
	int e= m_board->EncontraSapo();
	Coordenadas c1 (e/10, e-(e/10)*10, m_board->DirecaoSapo());		//Cria um objecto do tipo Coordenadas que guarda na stack a info do sapo
  	m_redo.push(c1);							
}

void CSameGame::GravaTabUndo()
{
	int e= m_board->EncontraSapo();
	Coordenadas c1(e/10, e-(e/10)*10, m_board->DirecaoSapo());
  	m_undo.push(c1);		       				      // Take the current board and put it on the undo
}

void CSameGame::UndoLast()
{
  if(m_undo.empty()) {GravaTabUndo(); return;} 		//  First make sure that there is a move to undo
  int e= m_board->EncontraSapo();
  Coordenadas c1,c2;	
  GravaTabRedo();	
  
    c1 = m_undo.top();
  if (c1.x==e/10 && c1.y==e-(e/10)*10){
  	m_undo.pop();
	c2 = m_undo.top();    							//  Take the top undo and make it the current
		m_board->SetBoard (e/10,e-(e/10)*10,1); 	//Substitui o sapo por uma folha
		m_board->SetBoard(c2.x,c2.y,c2.dir);		//e uma peça "água" pelo sapo
	m_undo.pop();	
  }
  else{
  		m_board->SetBoard (e/10,e-(e/10)*10,1); 	//Substitui o sapo por uma folha
		m_board->SetBoard(c1.x,c1.y,c1.dir);		//e uma peça "água" pelo sapo
		m_undo.pop();
  }     
}

bool CSameGame::CanUndo()
{
  return !m_undo.empty();     				// Can undo if the undo stack isn't empty
}

void CSameGame::RedoLast()
{
  int e= m_board->EncontraSapo();
  if(m_redo.empty()) return; 
  GravaTabUndo();  							// First make sure that there is a move to redo
  Coordenadas c2;
   	c2 = m_redo.top();									// Take the top redo and make it the current
	   	{ m_board->SetBoard (e/10,e-(e/10)*10,0);		//Substitui o sapo por uma casa vazia 
    	  m_board-> SetBoard(c2.x,c2.y,c2.dir); }		//Faz "load" da stack da posição do sapo
   m_redo.pop();
}

bool CSameGame::CanRedo()
{
  return !m_redo.empty();       // Can redo if the redo stack isn't empty
}

void CSameGame::ClearUndo()
{
  while(!m_undo.empty()) {      // Delete everything from the undo stack
    m_undo.pop();
  }
}

void CSameGame::ClearRedo()
{
  while(!m_redo.empty()) {      // Delete everything from the redo stack
    m_redo.pop();
  }
}
