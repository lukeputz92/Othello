/******************************************************************
    This is the header for the derived Game Othello
    Luke Putz           Fall 2016
**********************************************************************/
#ifndef OTHELLO_H
#define OTHELLO_H
#include <iostream>
#include "space.h"
#include "game.h"

using main_savitch_14::game;
   
class Othello:public game {   
  public:  
    enum player {HUMAN_PLAYER, COMP_PLAYER}; // Possible players    
   
    //Othello();         
    void make_move(const std::string& move);
    void restart();
    game::who winning() const;

    //boolean functions to check legal moves
    bool on_board(int row, int col) const;
    bool look_north(player p, int row, int col) const;
    bool look_south(player p, int row, int col) const;
    bool look_west(player p, int row, int col) const;
    bool look_east(player p, int row, int col) const;
    bool look_northwest(player p, int row, int col) const;
    bool look_northeast(player p, int row, int col) const;
    bool look_southwest(player p, int row, int col) const;
    bool look_southeast(player p, int row, int col) const;
    bool look_8(player p, int row, int col)const;

    //author's Purely Virtual functions
    game* clone( ) const;  
    void compute_moves(std::queue<std::string>& moves) const;
    void display_status( ) const; 
    int evaluate( ) const;
    bool is_game_over( ) const;
    bool is_legal(const std::string& move) const;

  private:   
    Space gameboard[8][8];//array of spaces for gameboard
    int passed;
};   

#endif
