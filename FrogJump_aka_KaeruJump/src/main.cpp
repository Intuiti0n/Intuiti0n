// 									Kaeru Jump
// Código adaptado por:
// Afonso Santos a73746		e		Daniel Gomes  a74729 , de
// Luis Paulo Reis, University of Minho, Portugal, lpreis@dsi.uminho.pt
// adapted From: Ben Marchant, "The Same Game: A Simple Game from Start to Finish", 2005

#include <iostream>    //Input/Output with streams: cout, cin
#include <cstdio>      //Input/Output: scanf and printf
#include <cstdlib>     //Standard Library: rand and pause
#include <ctime>       //ctime: includes function time
#include "SameGame.h"

using namespace std;

int main()
{
   CSameGame same;     // Creates an instance of the Game
   same.Game();        // Starts a new game
   system("pause"); 
   return 0;
}

