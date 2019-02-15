/******************************************************************
    This is the main to launch Othello
    Luke Putz           Fall 2016
**********************************************************************/
#include <iostream>
#include "game.h"
#include "othello.h"
#include "space.h"
#include "colors.h"
#include <string>
#include <cstdlib>
using namespace std;


int main(){
  Othello my_game;
  my_game.play();

  return EXIT_SUCCESS;
}

