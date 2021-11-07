// 									Kaeru Jump
// Código adaptado por:
// Afonso Santos a73746		e		Daniel Gomes  a74729 , de
// Luis Paulo Reis, University of Minho, Portugal, lpreis@dsi.uminho.pt
// adapted From: Ben Marchant, "The Same Game: A Simple Game from Start to Finish", 2005

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include "SameGameBoard.h"
#include <fstream>

#define ESCAPE 27 
#define BACKSPACE 8 
#define ENTER 13
#define S 15
using namespace std;

CSameGameBoard::CSameGameBoard(void)
: m_arrBoard(NULL), m_nColumns(10), m_nRows(10) 
{
    m_arrChars[0] = ' '; m_arrChars[1] = 'O'; m_arrChars[2] = 16;//seta pra direita
    m_arrChars[3] = 17;//seta pra esquerda
    m_arrChars[4] = 30;//seta pra cima
    m_arrChars[5] = 31;//seta pra baixo
    SetupBoard();              // Create and setup the board
	initwindow(SBO+3,SBO+7);   // Create the graphical window

}

CSameGameBoard::CSameGameBoard(const CSameGameBoard& board)
{
  //  Copy all of the regular data members
  m_nColumns = board.m_nColumns; m_nRows = board.m_nRows;
  m_arrBoard = NULL;
  CreateBoard();  //  Create a new game board of the same size
  for(int row = 0; row < m_nRows; row++)   //  Copy the contents of the game board
    for(int col = 0; col < m_nColumns; col++)
      m_arrBoard[row][col] = board.m_arrBoard[row][col];
}

CSameGameBoard::~CSameGameBoard(void)
{
  DeleteBoard();  //  Simply delete the board
}

void CSameGameBoard::SetupBoard(void)//Inicia_abul
{
  if(m_arrBoard == NULL) CreateBoard();     //  Create the board if needed
	char nome[11]="LevelX.txt";
   nome[5]=level+48;

  ifstream nivel (nome);
  for(int i = 0; i < m_nRows; i++) {   // Percorre todas as posiçoes do tabuleiro do ficheiro
    for(int j = 0; j < m_nColumns; j++){  
			nivel >> m_arrBoard[i][j]; //Carrega do ficheiro para a matriz do jogo
		} 
}	
}

void CSameGameBoard::SetBoard (int linhas, int colunas, int direcao)
{
	 m_arrBoard[linhas][colunas] = direcao;		// Função usada no undo/redo
}

int CSameGameBoard::GetBoardSpace(int row, int col)
{
  //  Check the bounds of the array
  if(row < 0 || row >= m_nRows || col < 0 || col >= m_nColumns)
    return m_arrChars[0];
//    return 4;
  return m_arrBoard[row][col];
}

void CSameGameBoard::DeleteBoard(void)
{
  if(m_arrBoard != NULL) {          // Don't delete a NULL board
    for(int row = 0; row < m_nRows; row++) {
      if(m_arrBoard[row] != NULL){
        delete [] m_arrBoard[row];  // Delete each row first
        m_arrBoard[row] = NULL;
      }
    }
    delete [] m_arrBoard;           // Finally delete the array of rows
    m_arrBoard = NULL;
  } 
}

void CSameGameBoard::CreateBoard(void)
{
  if(m_arrBoard != NULL) DeleteBoard();       //  If there is already a board, delete it
  m_arrBoard = new int*[m_nRows];             //  Create the array of rows
  for(int row = 0; row < m_nRows; row++){     //  Create each row
    m_arrBoard[row] = new int[m_nColumns];
    for(int col = 0; col < m_nColumns; col++) //  Set each square to be empty
      m_arrBoard[row][col] = 0;
  }
}

bool CSameGameBoard::IsLevelOver(void)
{
	int counter=0;
	for(int col = 0; col < m_nColumns; col++) {	 //  Go column by column, left to right
		for(int row =0 ; row<m_nRows; row++) {  	 //  Row by row, bottom to top
			if(m_arrBoard[row][col]==1) counter++; }
  	}
   // if(level==1&&counter==0){ IsGameOver(); } else	
  if (counter==0) {FimNivel();level++;cout<<"level complete."<<endl;return true;} // se so estiver o sapo acaba o jogo
  else return false;
}


bool CSameGameBoard::IsGameOver(void)  
{
	int counter=0;
	if(level==10){
		for(int col = 0; col < m_nColumns; col++) {	 //  Go column by column, left to right
			for(int row =0 ; row<m_nRows; row++)   	 //  Row by row, bottom to top
				if(m_arrBoard[row][col]==1) counter++; 
  		}
	if (counter==0) {FimJogo(); cout<<"Terminou o jogo"<<endl; return true;} // se so estiver o sapo acaba o jogo
	}
	else return false;
}

void CSameGameBoard::Save(){
	
	ofstream fich ("Save_Game.txt");
	for (int i=0; i<9; i++){
		for (int j=0; j<9; j++){
			fich << m_arrBoard[i][j] << " ";
		} fich << endl;
	}
	fich << level << endl; 
	fich << tentativas << endl;
	fich << DrawValid << endl << DrawHint << endl << DoUndoRedo << endl << DrawEyes << Auto_Save << endl << m_nmoves;
} 

void CSameGameBoard::Load(){
	
	ifstream fich ("Save_Game.txt");
	for (int i=0; i<9; i++){
		for (int j=0; j<9; j++){
			fich >> m_arrBoard[i][j]; 
		} 
	}
	fich >> level;
	fich >> tentativas;
	fich >> DrawValid >> DrawHint >> DoUndoRedo >> DrawEyes >> Auto_Save >> m_nmoves;
}


int CSameGameBoard::deteta_tecla(){
	int T = 0;
    while(!IsGameOver())
    {
        switch((T=getch())) {
        case KEY_UP:
            T=4; return T;	//Key Up
        case KEY_DOWN:
            T=5; return T;	//Key Down
        case KEY_LEFT:
            T=3; return T;	//Key Left
        case KEY_RIGHT:
            T=2; return T;  //Key Right
        case ENTER:
        	T=6; return T;	//Reset level
        case BACKSPACE:
        	T=7; return T;  //Reset game
        case 's': case 'S':
        	T=8; return T;	//Save game
        case 'l':case 'L':
        	T=9; return T;	//Load game
        case 'h': 
        	T=13; return T;	//Hint
        case 'r':case 'R':
        	T=10; return T;	//Redo
        case 'u':case 'U':
        	T=11; return T; //Undo			
        case 27: case 'p':
        	T=12; return T;	//Menu Pausa
        default: break;
        }
    } 
}

int CSameGameBoard::DirecaoSapo(){
	int D=0;
	for(int row = 0; row < m_nRows; row++)   //Procura o sapo e diz-nos para onde está virado
    for(int col = 0; col < m_nColumns; col++){	
    	if(m_arrBoard[row][col]==2) D=2;		//Direita
		if(m_arrBoard[row][col]==3) D=3;		//Esquerda
		if(m_arrBoard[row][col]==4) D=4;		//Cima
		if(m_arrBoard[row][col]==5) D=5;		//Baixo
	} return D;
}

int CSameGameBoard::EncontraSapo(){
	int i=0, j=0;							//encontra sapo
	for(int row = 0; row < m_nRows; row++)   
    for(int col = 0; col < m_nColumns; col++){
    	if(m_arrBoard[row][col]==2||m_arrBoard[row][col]==3||m_arrBoard[row][col]==4||m_arrBoard[row][col]==5){
    		return (10*row+col);  	//Retorna as coordenadas do sapo
    	}
    }
}

// Checks if a given move is valid on the board
bool CSameGameBoard::ValidMove(int T, int D){	//Se a tecla premida for a do sentido contrario 
												//da direçao do sapo, retorna falso
	 if (D==2 && T==3) return false;		
	 else if (D==5 && T==4) return false;
	 else if (D==3 && T==2) return false;
	 else if (D==4 && T==5) return false;
	 else return true;
}


int CSameGameBoard::Direita(){
	int i=EncontraSapo()/10, j=EncontraSapo() - (EncontraSapo()/10)*10;
	for (int a=j; a<9; a++){			// A Procura começa na posição do sapo e vai ate ao limite direito do tabuleiro 
 		if (m_arrBoard[i][a]==1) return a;}			
	return 'c';							//Quando não há casa vazia devolve 'c' (como se fosse erro)
}

int CSameGameBoard::Esquerda(){
	int i=EncontraSapo()/10, j=EncontraSapo() - (EncontraSapo()/10)*10;
	for (int a=j; a>=0; a--){			// A Procura começa na posição do sapo ate ao limite esquerdo do tabuleiro 
 		if (m_arrBoard[i][a]==1) return a;}
	return 'c';}

int CSameGameBoard::Cima(){
	int i=EncontraSapo()/10, j=EncontraSapo() - (EncontraSapo()/10)*10;
	for (int a=i; a>=0; a--){			// A Procura começa na posição do sapo e "sobe" ate ao início da coluna/tabuleiro
 		if (m_arrBoard[a][j]==1) return a;}
	return 'c'; } 

int CSameGameBoard::Baixo(){
	int i=EncontraSapo()/10, j=EncontraSapo() - (EncontraSapo()/10)*10;
	for (int a=i; a<9; a++){			// A Procura começa na posição do sapo começa a "descer" ate chegar ao fim da coluna/tabuleiro
 		if (m_arrBoard[a][j]==1) return a;}
 	return 'c';
}

int CSameGameBoard::executa_movimento(int T, int D){
	int i=EncontraSapo()/10,  j=EncontraSapo() - (EncontraSapo()/10)*10;

	 if (T==2)  {if(ValidMove(T,D)) {			// Se for para a DIREITA
	 				int M=0, a=Direita();		// A variável M deteta se a jogada foi executada. Serve para contar os movimentos	
	 				if(Direita()!='c') {m_arrBoard[i][j]=0; m_arrBoard[i][a-(a/10)*10]=2; return M=1;} } //Troca a posiçao onde tava o sapo por uma casa vazia 	 	
				else return 0;  }

else if (T==3)	{if(ValidMove(T,D)) {			// Se for para a ESQUERDA
	 				int M=0, a=Esquerda();
					 if(Esquerda()!='c') {m_arrBoard[i][j]=0; m_arrBoard[i][a]=3; return M=1;}}
				else return 0; }	
				
else if (T==4)	{if(ValidMove(T,D)) {			// Se for para CIMA
					int M=0, a=Cima();
					if(Cima()!='c') {m_arrBoard[i][j]=0; m_arrBoard[a][j]=4; return M=1;}}
				else return 0;}	
	
else if (T==5)	{if(ValidMove(T,D)) {			// Se for para BAIXO
					int M=0, a=Baixo();
					if(Baixo()!='c') {m_arrBoard[i][j]=0; m_arrBoard[a][j]=5; return M=1;}}
				else return 0;}
}

// Shows the Board in a text manner
void CSameGameBoard::DrawBoard(void)
{
  if (GRAPH) DrawGraphBoard();
  cout << "\t\tKaeru Jump " << endl << "   ";    
  for(int col = 0; col < m_nColumns; col++) printf("%2d  ",col+1); 
  printf("\n");
  for(int row = 0; row < m_nRows; row++){
  	cout<<"  |---|---|---|---|---|---|---|---|---|"<<endl;
    printf("%2d",row+1);
    for(int col = 0; col < m_nColumns; col++){ 
	
    cout << "| " << m_arrChars[GetBoardSpace(row, col)]<<" ";}//conv peca  }
    cout <<"|"<< endl;
}	cout<<"  |---|---|---|---|---|---|---|---|---|"<<endl;
}

void CSameGameBoard::menu(){
	cleardevice();
	setbkcolor(0);
	setcolor(15);
	setfillstyle(6,4);
	bar(0,0,SBO,SBO);
	settextstyle(3,0,5); outtextxy(150,15,"Kaeru Jump");
	settextstyle(3,0,3); outtextxy(50,130,"1. Novo Jogo");
	outtextxy(50,180,"2. Carregar Jogo Guardado");  
	outtextxy(50,230,"3. Regras");  
	outtextxy(50,280,"4. Controlos");  
	outtextxy(50,330,"5. Opções"); 
	outtextxy(50,380,"6. Sair"); 
	settextstyle(3,0,2); outtextxy(400,500,"Desenvolvido por:");
	outtextxy(400,525,"Afonso Santos");
	outtextxy(400,550,"Daniel Gomes");	
	
	int c=0;
        switch(c=getch()) {
        case '1':
        	DrawBoard(); break;
        case '2':
            Load(); DrawBoard(); break;
        case '3':
        	Regras(); break;
        case '4':
        	Controlos(); break;
        case '5':
        	Opcoes(); break;
		case '6':
			exit(1); 
		default:
			menu();
    	}
}

void CSameGameBoard::Regras()
{
	//cleardevice();
	setfillstyle(1,0);
	setcolor(0);
	setbkcolor(0);
	bar (0, 0, SBO, SBO+140);
	setcolor(3);
	settextstyle(BOLD_FONT, HORIZ_DIR, 4);
	outtextxy((SBO/3)+20,50,"Regras");
	setcolor(15);
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, 1);
	outtextxy(10,150,"Kaeru Jump é um jogo de apenas um jogador em que");
	outtextxy(10,180,"o objetivo é passar por todas as casas de cada nível;");
	outtextxy(10,230,"Cada vez que o sapo salta para uma casa esta será");
	outtextxy(10,260,"removida e o jogador não poderá passar por ela");
	outtextxy(10,290,"novamente;");
	outtextxy(10,340,"Apenas se pode jogar na vertical/horizontal e não");
	outtextxy(10,370,"é possível jogar para a posição oposta ao sapo.");
	//setbkcolor(15);
	setfillstyle(1,0);
	settextstyle(BOLD_FONT, HORIZ_DIR, 1);
	outtextxy (40,560,"»Para voltar ao Menu Principal prima 'ENTER'");
//	setbkcolor(0);
	while(getch()!=13){ } if (pausa==1) Pausa(); else menu();
}

void CSameGameBoard::Controlos(){
	setfillstyle(1,0);
	setcolor(0);
	setbkcolor(0);
	bar (0, 0, SBO, SBO+140);
	setcolor(2);
	settextstyle(BOLD_FONT, HORIZ_DIR, 4);
	outtextxy((SBO/3)-10,50,"Controlos");
	setcolor(15);
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, 1);
	outtextxy(90,140,"»Use as setas para controlar o sapo");
	outtextxy(30,190,"'ENTER'  -  Reset nível");
	outtextxy(30,230,"'ESC' ou 'p'  -  Menu Pausa");
	outtextxy(30,270,"'BACKSPACE'  -  Reset jogo ");
	outtextxy(30,300,"'s'  -  Save");
	outtextxy(30,340,"'l'  -  Load (Só pode fazer 1 load por nível)");
	outtextxy(30,380,"'u'  -  Undo");
	outtextxy(30,420,"'r'  -  Redo");
	outtextxy(30,460,"'h'  -  Hint/Ajuda");
	//setbkcolor(15);
	setfillstyle(1,0);
	settextstyle(BOLD_FONT, HORIZ_DIR, 1);
	outtextxy (40,560,"»Para voltar ao Menu Principal prima 'ENTER'");
//	setbkcolor(0);
	while(getch()!=13){ } if (pausa==1) Pausa(); else menu();
}


void CSameGameBoard::Opcoes(){
	int c=1;
	while(c!=13){
	setfillstyle(1,0); setcolor(0); setbkcolor(0);
	bar (0, 0, SBO, SBO+140); setcolor(2);
	settextstyle(BOLD_FONT, HORIZ_DIR, 4);
	outtextxy((SBO/3)-10,50,"Opções");
	setcolor(15);
	settextstyle(BOLD_FONT, HORIZ_DIR, 1);
	outtextxy(400,140,"Estado");
	outtextxy(30,180,"1. Mostrar Jogadas Válidas"); if (DrawValid==1) outtextxy(425,180,"On"); else outtextxy(425,180,"Off");
	outtextxy(30,230,"2. Hint"); if (DrawHint==1) outtextxy(425,230,"On"); else outtextxy(425,230,"Off");
	outtextxy(30,280,"3. Undo e Redo"); if (DoUndoRedo==1) outtextxy(425,280,"On"); else outtextxy(425,280,"Off");
	outtextxy(30,330,"4. Desenhar olhos no sapo"); if (DrawEyes==1) outtextxy(425,330,"On"); else outtextxy(425,330,"Off");	
	outtextxy(30,380,"5. Auto Save (no fim do nível)"); if (Auto_Save==1) outtextxy(425,380,"On"); else outtextxy(425,380,"Off");
	outtextxy (40,560,"»Para voltar ao Menu Principal prima 'ENTER'");	

	switch (c=getch()){
		case '1': 
			if (DrawValid==1) DrawValid=0;
				else DrawValid=1; break;
		case '2':
			if (DrawHint==1) DrawHint=0;
				else DrawHint=1; break;
		case '3':
			if(DoUndoRedo==1) DoUndoRedo=0;
				else DoUndoRedo=1; break;
		case '4':		
			if(DrawEyes==1) DrawEyes=0;
				else DrawEyes=1; break;
		case '5':
			if(Auto_Save==1) Auto_Save=0;
				else Auto_Save=1; break;
		}		
	}
	 if (pausa==1) Pausa(); else menu();	
}



void CSameGameBoard::Pausa(){
	pausa=1;
	cleardevice();
	setbkcolor(0);
	setcolor(15);
	setfillstyle(6,4);
	bar(0,0,SBO,SBO);
	settextstyle(3,0,5); outtextxy(185,65,"Pausa"); settextstyle(3,0,3); 
	outtextxy(50,180,"1. Continuar");
	outtextxy(50,230,"2. Regras");  
	outtextxy(50,280,"3. Controlos"); 
	outtextxy(50,330,"4. Opções"); 
	outtextxy(50,380,"5. Sair (sem guardar o jogo)"); 
	
	int c=0;
        switch(c=getch()) {
        case '1': case 27: case'p':
        	return;
        case '2':
        	Regras(); break;
        case '3':
        	Controlos(); break;
		case '4':
			Opcoes(); break;
		case '5':
			exit(1);
		default:
			Pausa();
    	}
}


int CSameGameBoard::Recorde(){
	int recorde;
	char nome[13]="RecordeX.txt";
    nome[7]=level+48;
  	ifstream max (nome); { max >> recorde; }
	ifstream max1 (nome); { max1 >> old_recorde;}
	if (recorde > tentativas) { 
		recorde=tentativas;
		ofstream maxout (nome);
		maxout<<recorde; 
		max.close(); maxout.close(); 
		return 1; }
	
	else return 0;
}

void CSameGameBoard::FimNivel(void){
	
	cleardevice();
  	if (Recorde()==1) {old_recorde=tentativas; setcolor(4);settextstyle(10,0,5); outtextxy(125,150,"Novo Recorde!"); 
					   settextstyle(3,0,2); outtextxy(190,405,"Novo");}
	char rec[4]= "XXX";
		if (old_recorde<10) { rec[0]=' ';rec[1]=' '; rec[2]= old_recorde+48;}
		if (old_recorde>10|| old_recorde<100) { rec[0]=' ';rec[1]=(old_recorde/10)+48;rec[2]= old_recorde-((old_recorde/10)*10)+48;}
    	if (old_recorde>=100) { rec[0]=(old_recorde/100)+48; rec[1]=((old_recorde-((old_recorde/100)*100))/10)+48;rec[2]= old_recorde-((old_recorde/10)*10)+48;}
	char ten[26]="Número de tentativas: XXX";
		if (tentativas<10) { ten[22]=' ';ten[23]=' '; ten[24]= tentativas+48;}
		if (tentativas>10|| tentativas<100) { ten[22]=' ';ten[23]=(tentativas/10)+48;ten[24]= tentativas-((tentativas/10)*10)+48;}
    	if (tentativas>=100) { ten[22]=(tentativas/100)+48; ten[23]=((tentativas-((tentativas/100)*100))/10)+48;ten[24]= tentativas-((tentativas/10)*10)+48;}
     	
	settextjustify(1,1); settextstyle(10,0,5); setbkcolor(3); setcolor(2);outtextxy(300,200,"Parabéns!");
	settextstyle(9,0,5); outtextxy(300,300,"Completou o nível"); settextstyle(9,0,4);outtextxy(300,350,ten); 
	settextstyle(3,0,2); outtextxy(285,400,"Recorde: "); outtextxy(340,400,rec);			   
	settextstyle(3,0,2); outtextxy(300,550,"Prima 'ENTER' para continuar");
	while(getch()!=13){ } 
}

int CSameGameBoard::FimJogo(void){
	
	cleardevice();
	settextjustify(1,1); settextstyle(10,0,5); setbkcolor(3); setcolor(2);outtextxy(300,200,"Parabéns!");
	settextstyle(9,0,5); outtextxy(300,300,"Acabou o Jogo!!");
	settextstyle(9,0,3);outtextxy(300,350,"Deseja começar de novo?");outtextxy(300,400,"'s' - Sim");outtextxy(300,450,"'n' - Não");  
	switch (getch()){
		case 's': level=0; DrawBoard(); return 1;
		case 'n': exit(1);
		default: FimJogo();
	}
}

void CSameGameBoard::CarregaHint(){

	char hint[13]="HintX.txt";
    hint[4]=level+48;
    ifstream Hint (hint);
    
    for(int i = 0; i < m_nRows; i++) 	// Percorre todas as posiçoes do tabuleiro do ficheiro 
    	for(int j = 0; j < m_nColumns; j++) 
			Hint >> m_hint[i][j]; 
}


void CSameGameBoard::Hint(void){
    							// i -> Linhas		j -> Colunas
    	int i_sapo=EncontraSapo()/10,  j_sapo=EncontraSapo() - (EncontraSapo()/10)*10;
	int hint_i, hint_j, hint_inew, hint_jnew, i_anterior, j_anterior;
	
	int pos_h = m_hint[i_sapo][j_sapo]; 
	int new_pos = pos_h+1;
		for(int hint_i=0; hint_i<9; hint_i++)
			for (int hint_j=0; hint_j<9; hint_j++){
				if(m_hint [hint_i][hint_j]==new_pos)	 { hint_inew = hint_i;	hint_jnew = hint_j; }	
				if (m_hint [hint_i][hint_j]==new_pos-1)  { i_anterior = hint_i; j_anterior = hint_j; }	// Posiçao onde o sapo deveria estar
			}
 									
	int sqC=SBO/m_nColumns, sqR=SBO/m_nRows; setcolor(0); setfillstyle(9, 14);
	if(Cima()==hint_inew && hint_jnew==j_sapo&&pos_h==m_nmoves)
		{while(!kbhit()) fillellipse(j_sapo*sqR+sqR/2,hint_inew*sqC+sqC/2,sqR/2-7,sqC/2-7);}
	else if(Baixo()==hint_inew && hint_jnew==j_sapo&&pos_h==m_nmoves)
		{while(!kbhit()) fillellipse(j_sapo*sqR+sqR/2,hint_inew*sqC+sqC/2,sqR/2-7,sqC/2-7);}
	else if(Esquerda()==hint_jnew && hint_inew==i_sapo&&pos_h==m_nmoves)
		{while(!kbhit()) fillellipse(hint_jnew*sqR+sqR/2,i_sapo*sqC+sqC/2,sqR/2-7,sqC/2-7); }
	else if(Direita()==hint_jnew && hint_inew==i_sapo&&pos_h==m_nmoves)
		{while(!kbhit()) fillellipse(hint_jnew*sqR+sqR/2,i_sapo*sqC+sqC/2,sqR/2-7,sqC/2-7); }
	else {settextjustify(1,1);settextstyle(9,0,4);setcolor(4); outtextxy(300,300,"Não posso ajudá-lo!!"); delay(700);}
}


// Shows the Board in a simple Graphical manner (squares and circles)
void CSameGameBoard::DrawGraphBoard(void)
{
	setfillstyle(1,3);
	bar(0,0,SBO,SBO);
	int sqC=SBO/m_nColumns, sqR=SBO/m_nRows; 
	
	char ten[16]="Tentativas: XXX";
		if (tentativas<10) { ten[12]=' ';ten[13]=' '; ten[14]= tentativas+48;}
		if (tentativas>10|| tentativas<100) { ten[12]=' ';ten[13]=(tentativas/10)+48;ten[14]= tentativas-((tentativas/10)*10)+48;}
		if (tentativas>=100) { ten[12]=(tentativas/100)+48; ten[13]=((tentativas-((tentativas/100)*100))/10)+48;ten[14]= tentativas-((tentativas/10)*10)+48;}
	char nome[11]="Level XX";
    if (level!=9){nome[6]=level+49; nome[7]=' ';}	else {nome[6]=level/10+49; nome[7]='0';}
				//Atençao que os j e os i estao trocados			
						//i= colunas; j=linhas
	for(int i=0; i<m_nColumns; i++)  
        for(int j=0; j<m_nRows; j++) {
        		settextjustify(0,0); settextstyle(0,0,4); setbkcolor(3); setcolor(2);outtextxy(10,40,nome); settextstyle(8,0,2); outtextxy(300,32.5,ten);  // ou letra 7 
			int pec=GetBoardSpace(j,i);
			if (pec>0) {
				if(pec==1){	setcolor(14); setfillstyle(1, 14);}
				else{setcolor(2); setfillstyle(1, 2);}
				fillellipse(i*sqR+sqR/2,j*sqC+sqC/2,sqR/2-7,sqC/2-7);  //peca
			if (DrawEyes==1){
				if (pec==2) {	setcolor(0);setfillstyle(1,0);
							fillellipse(i*sqR+sqR/10+40,j*sqC+sqC/10+17,sqR/10,sqC/10); //desenha os olhos do sapo
							fillellipse(i*sqR+sqR/10+40,j*sqC+sqC/10+33,sqR/10,sqC/10);}//virado para a direita
				if (pec==3) {	setcolor(0);setfillstyle(1,0);	
							fillellipse(i*sqR+sqR/10+12,j*sqC+sqC/10+19,sqR/10,sqC/10);//esquerda
							fillellipse(i*sqR+sqR/10+12,j*sqC+sqC/10+35,sqR/10,sqC/10);}
				if (pec==4) {setcolor(0);setfillstyle(1,0);
							fillellipse(i*sqR+sqR/10+19,j*sqC+sqC/10+12,sqR/10,sqC/10);//cima
							fillellipse(i*sqR+sqR/10+35,j*sqC+sqC/10+12,sqR/10,sqC/10);}
				if (pec==5) {setcolor(0);setfillstyle(1,0);
							fillellipse(i*sqR+sqR/10+19,j*sqC+sqC/10+40,sqR/10,sqC/10);//baixo
							fillellipse(i*sqR+sqR/10+35,j*sqC+sqC/10+40,sqR/10,sqC/10);}
				}
			}
		}		
		if (DrawValid==1){				//Parte que "desenha" as jogadas válidas
			{setcolor(5); setfillstyle(9, 1); int j=EncontraSapo()/10, i= EncontraSapo() - (EncontraSapo()/10)*10;
			if(DirecaoSapo()!=2) fillellipse(Esquerda()*sqR+sqR/2+10,j*sqC+sqC/2-10,5,5);	//Direita
			if(DirecaoSapo()!=3) fillellipse(Direita()*sqR+sqR/2+10,j*sqC+sqC/2-10,5,5);	//Esquerda
			if(DirecaoSapo()!=4) fillellipse(i*sqR+sqR/2+10,Baixo()*sqC+sqC/2-10,5,5);		//Cima
			if(DirecaoSapo()!=5) fillellipse(i*sqR+sqR/2+10,Cima()*sqC+sqC/2-10,5,5); }		//Baixo
		}
}		
