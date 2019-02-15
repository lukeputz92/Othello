/******************************************************************
    This is the implementation for the derived Game Othello
    Luke Putz           Fall 2016
**********************************************************************/
#include "othello.h"
#include "space.h"
#include "colors.h"
#include <string>

using namespace std;

//Mr D. I deleted the constructor and destructor because they seemed
//to be causing segfaults, I hope that is ok. 
/*Othello::Othello() {
  restart();
}*/

game* Othello::clone( ) const{
  return new Othello(*this);
}

void Othello::restart(){
  //walk array and set all pieces to blank
  for (int i = 0; i < 8; ++i){
    for (int j = 0; j < 8; ++j){
      gameboard[j][i].set_color(Space::AVAILABLE);
    }
  }

  //set starting positions for black & white
  gameboard[3][4].set_color(Space::BLACK);
  gameboard[4][3].set_color(Space::BLACK);
  gameboard[3][3].set_color(Space::WHITE);
  gameboard[4][4].set_color(Space::WHITE);
  game::restart();
}

//make a board
void Othello::display_status() const{
  cout << "  ";
  cout << "-----A---------B---------C----------D---------E---------F---------G--------H----";  
  for (int j = 0; j < 8; ++j){
    cout << endl << RED << (j+1)<< " " << BLUE << "|" <<RESET; 
    for (int i = 0; i < 8; ++i){
      gameboard[j][i].output();//output spaces in inner loop
      if(gameboard[j][i].get_color() == Space::WHITE)
        cout << B_WHITE << BLUE << "  " << RESET <<B_GREEN <<BLUE << "|" << RESET;
      else if(gameboard[j][i].get_color() == Space::BLACK)
        cout << B_BLACK << BLUE << "  " << RESET <<B_GREEN <<BLUE << "|" << RESET;
      else
        cout << B_GREEN << BLUE << "  "<< RESET <<B_GREEN <<BLUE << "|" << RESET;

    }
    cout << BLUE << "\n  |";  
    for (int i = 0; i < 8; ++i){
      if(gameboard[j][i].get_color() == Space::WHITE)
        cout << B_WHITE << BLUE <<"_________" << RESET <<B_GREEN <<BLUE << "|" << RESET;
      else if(gameboard[j][i].get_color() == Space::BLACK)
        cout << B_BLACK << BLUE <<"_________" << RESET <<B_GREEN <<BLUE << "|" << RESET;
      else
        cout << B_GREEN <<BLUE<< "_________" << RESET <<B_GREEN << BLUE << "|" << RESET;
    }
  }
  cout << RESET << endl << endl;
}

//calls is_legal to check, sets spacecolor & flips
//by calling the respective look function and flipping every opp color
void Othello::make_move(const string& move){
  int row, col;
  if(!move.empty()){
    col = int(toupper(move[0]) - 'A');
    row = int(toupper(move[1]) - '1');
  }

  Space::color c;
  player plyr;

  if(move == "pass")
    passed++;

  if(next_mover() == HUMAN){
    c = Space::BLACK;
    plyr = HUMAN_PLAYER;
  }
  else if(next_mover() == COMPUTER){
    c = Space::WHITE;
    plyr = COMP_PLAYER;

  }
      if(on_board(row, col) == true)
        gameboard[row][col].set_color(c);

      if (look_north(plyr, row, col)) {
        for(int i = row - 1;on_board(i, col) ==true && (gameboard[i][col].get_color() !=c); --i){
          gameboard[i][col].flip();
        }             
      }
      if (look_south(plyr, row, col)) {
        for(int i = row + 1;on_board(i, col) ==true && (gameboard[i][col].get_color() !=c); ++i){
          gameboard[i][col].flip();
        }             
      }
      if (look_west(plyr, row, col)) {
        for(int j = col - 1; on_board(row, j) ==true && (gameboard[row][j].get_color() !=c); --j){
          gameboard[row][j].flip();
        }             
      }
      if (look_east(plyr, row, col)) {
        for(int j = col + 1;on_board(row, j) == true && (gameboard[row][j].get_color() !=c); ++j){
          gameboard[row][j].flip();
        }             
      }
      if (look_northwest(plyr, row, col)) {
        for(int i=row-1, j=col-1;on_board(i,j) ==true && (gameboard[i][j].get_color() !=c);--i, --j){
          gameboard[i][j].flip();
        }             
      }
      if (look_northeast(plyr, row, col)) {
        for(int i=row-1, j=col+1; on_board(i,j) == true && (gameboard[i][j].get_color() !=c); --i, ++j){
          gameboard[i][j].flip();
        }             
      }
      if (look_southwest(plyr, row, col)) {
         for(int i=row+1, j=col-1; on_board(i,j) ==true && (gameboard[i][j].get_color() !=c); ++i, --j){
          gameboard[i][j].flip();
        }             
      }
      if (look_southeast(plyr, row, col)) {
        for(int i=row+1, j=col+1; on_board(i,j) ==true && (gameboard[i][j].get_color() !=c); ++i, ++j){
          gameboard[i][j].flip();
        }             
      }

  game::make_move(move);
}

//all look functions use for loops to determine if a sandwich can be made
//in the respective direction depending on the player's color 
bool Othello::look_north(player p, int row, int col) const{

  if (p == HUMAN_PLAYER){
    if(on_board(row -1, col)==true && gameboard[row -1][col].get_color() == Space::WHITE){
      int i;
      for(i = row -1;on_board(i, col) == true && gameboard[i][col].get_color() != Space::AVAILABLE 
        && gameboard[i][col].get_color() != Space::BLACK; --i);
    
      return(on_board(i, col) ==true && gameboard[i][col].get_color() == Space::BLACK);
      }
    }

  else if (p == COMP_PLAYER){
    if(on_board(row -1, col) ==true && gameboard[row -1][col].get_color() == Space::BLACK){
      int i;
      for(i = row -1;on_board(i, col) == true && gameboard[i][col].get_color() != Space::AVAILABLE 
        && gameboard[i][col].get_color() != Space::WHITE; --i);

      return (on_board(i, col) ==true && gameboard[i][col].get_color() == Space::WHITE);
    }
  }
  return false;
}

bool Othello::look_south(player p, int row, int col) const{

  if(p == HUMAN_PLAYER){
    if(on_board(row +1, col) == true && gameboard[row +1][col].get_color() == Space::WHITE){
      int i;
      for(i = row +1; (on_board(i, col) == true && gameboard[i][col].get_color() != Space::BLACK) 
        && (gameboard[i][col].get_color() != Space::AVAILABLE); ++i);

      return(on_board (i, col) ==true && gameboard[i][col].get_color() == Space::BLACK);
      }
    }

  else if (p == COMP_PLAYER){
    if(on_board(row +1, col) == true && gameboard[row +1][col].get_color() == Space::BLACK){
      int i;
      for(i = row +1; on_board(i, col) == true &&  gameboard[i][col].get_color() != Space::WHITE 
            && gameboard[i][col].get_color() != Space::AVAILABLE; ++i);
    
    return(on_board(i, col) == true && gameboard[i][col].get_color() == Space::WHITE);
    }
  }
  return false;
}

bool Othello::look_west(player p, int row, int col) const{

  if(p == HUMAN_PLAYER){
    if(on_board(row, col-1) ==true && gameboard[row][col -1].get_color() == Space::WHITE){
      int i;
      for(i = col -1; on_board(row, i) == true && gameboard[row][i].get_color() != Space::BLACK 
            && gameboard[row][i].get_color() != Space::AVAILABLE; --i);

      return(on_board(row, i) == true && gameboard[row][i].get_color() == Space::BLACK);
    }
  }

  else if(p == COMP_PLAYER){
    if(on_board(row, col -1) == true && gameboard[row][col -1].get_color() == Space::BLACK){
      int i;
      for(i = col -1; on_board(row, i) == true &&  gameboard[row][i].get_color() != Space::WHITE 
            && gameboard[row][i].get_color() != Space::AVAILABLE; --i);

      return(on_board(row, i) ==true && gameboard[row][i].get_color() == Space::WHITE);
    }
  }
  return false;
}

bool Othello::look_east(player p, int row, int col) const{

  if(p == HUMAN_PLAYER){
    if(on_board(row, col+1) ==true && gameboard[row][col +1].get_color() == Space::WHITE){
      int i;
      for(i = col +1; on_board(row, i) == true && gameboard[row][i].get_color() != Space::BLACK
            && gameboard[row][i].get_color() != Space::AVAILABLE; ++i);

      return (on_board(row, i) ==true && gameboard[row][i].get_color() == Space::BLACK);
    } 
  }

  else if (p == COMP_PLAYER){
    if(on_board(row, col+1) ==true && gameboard[row][col +1].get_color() == Space::BLACK){
      int i;
      for(i = col +1; on_board(row, i) == true && gameboard[row][i].get_color() != Space::WHITE 
            && gameboard[row][i].get_color() != Space::AVAILABLE; ++i);

      return(on_board(row, i) == true && gameboard[row][i].get_color() == Space::WHITE);
    }    
  }
  return false;
}

bool Othello::look_northwest(player p ,int row, int col) const{
  if(p == HUMAN_PLAYER){
    if(on_board(row -1, col -1) == true && gameboard[row -1][col -1].get_color() == Space::WHITE){
      int i, j;
      for(i = row -1, j = col -1; on_board(i, j) == true && gameboard[i][j].get_color() != Space::BLACK 
            && gameboard[i][j].get_color() != Space::AVAILABLE; --i, --j);
      
      return(on_board(i,j) == true && gameboard[i][j].get_color() == Space::BLACK);
    }  
  }

  else if(p == COMP_PLAYER){
    if(on_board(row-1, col-1) ==true && gameboard[row -1][col -1].get_color() == Space::BLACK){
      int i, j;
      for(i = row -1, j = col -1;on_board(i,j) == true && gameboard[i][j].get_color() != Space::WHITE 
            && gameboard[i][j].get_color() != Space::AVAILABLE; --i, --j);
      
      return (on_board(i,j) == true && gameboard[i][j].get_color() == Space::WHITE);
    }
  }
  return false;
}

bool Othello::look_northeast(player p, int row, int col) const{

  if(p == HUMAN_PLAYER){
    if(on_board(row -1, col +1) == true && gameboard[row -1][col +1].get_color() == Space::WHITE){
      int i, j;
      for(i = row -1, j = col +1; on_board(i, j) == true &&  gameboard[i][j].get_color() != Space::BLACK 
            && gameboard[i][j].get_color() != Space::AVAILABLE; --i, ++j);

      return(on_board(i, j) && gameboard[i][j].get_color() == Space::BLACK);
    }   
  }

  else if(p == COMP_PLAYER){
    if(on_board (row-1, col+1) ==true && gameboard[row -1][col +1].get_color() == Space::BLACK){
      int i, j;
      for(i = row -1, j = col +1; on_board(i, j) == true &&  gameboard[i][j].get_color() != Space::WHITE 
            && gameboard[i][j].get_color() != Space::AVAILABLE; --i, ++j);

      return (on_board(i, j) && gameboard[i][j].get_color() == Space::WHITE);  
    }
  }
  return false;
}

bool Othello::look_southwest(player p, int row, int col) const{

  if(p == HUMAN_PLAYER){
    if(on_board(row+1, col-1) == true && gameboard[row +1][col -1].get_color() == Space::WHITE){
      int i, j;
      for(i = row +1, j = col -1; on_board(i, j) == true &&  gameboard[i][j].get_color() != Space::BLACK 
            && gameboard[i][j].get_color() != Space::AVAILABLE; ++i, --j);
      
      return (on_board(i, j) == true && gameboard[i][j].get_color() == Space::BLACK);
    }
  }

  else if(p == COMP_PLAYER){
    if(on_board(row +1, col -1) == true && gameboard[row +1][col -1].get_color() == Space::BLACK){
      int i, j;
      for(i = row +1, j = col -1; on_board(i, j) == true &&  gameboard[i][j].get_color() != Space::WHITE 
            && gameboard[i][j].get_color() != Space::AVAILABLE; ++i, --j);
      
      return(on_board(i,j) == true && gameboard[i][j].get_color() == Space::WHITE);
    }   
  }
  return false;
}

bool Othello::look_southeast(player p, int row, int col) const{

  if(p == HUMAN_PLAYER){
    if(on_board(row+1, col+1) ==true && gameboard[row +1][col +1].get_color() == Space::WHITE){
      int i, j;
      for(i = row +1, j = col +1; on_board(i, j) == true &&  gameboard[i][j].get_color() != Space::BLACK 
            && gameboard[i][j].get_color() != Space::AVAILABLE; ++i, ++j);

      return (on_board(i,j) == true && gameboard[i][j].get_color() == Space::BLACK);
    }
  }

  else if(p == COMP_PLAYER){
    if(on_board(row+1,col+1) == true && gameboard[row +1][col +1].get_color() == Space::BLACK){
      int i , j;
      for(i = row +1, j = col +1;on_board(i, j) == true &&  gameboard[i][j].get_color() != Space::WHITE 
            && gameboard[i][j].get_color() != Space::AVAILABLE; ++i, ++j);

      return (on_board(i,j) == true && gameboard[i][j].get_color() == Space::WHITE);
    }
  }
  return false;
}
//check all 8 directions combined
bool Othello::look_8(player p, int row, int col)const{
    if (p == HUMAN_PLAYER && on_board(row, col) ==true){
    return (look_north(HUMAN_PLAYER, row, col)  || look_south(HUMAN_PLAYER, row, col) 
            || look_west(HUMAN_PLAYER, row, col) || look_east(HUMAN_PLAYER, row, col) 
            || look_northwest(HUMAN_PLAYER, row, col) || look_northeast(HUMAN_PLAYER, row, col)
            || look_southwest(HUMAN_PLAYER, row, col) || look_southeast(HUMAN_PLAYER, row, col));
  }

  else{
    return (look_north(COMP_PLAYER, row, col)  || look_south(COMP_PLAYER, row, col) 
            || look_west(COMP_PLAYER, row, col) || look_east(COMP_PLAYER, row, col) 
            || look_northwest(COMP_PLAYER, row, col) || look_northeast(COMP_PLAYER, row, col)
            || look_southwest(COMP_PLAYER, row, col) || look_southeast(COMP_PLAYER, row, col));   
  }
}

//check if space is empty & on board then check all 8 directions
bool Othello::is_legal(const string& move) const{
  int row, col;
    col = int(toupper(move[0]) - 'A');
    row = int(toupper(move[1]) - '1');

  if (move == "pass") return true; //in case player has no move
  else if(!on_board(row, col)) return false;

  else if (next_mover() == HUMAN && gameboard[row][col].get_color() == Space::AVAILABLE){
    return (look_8(HUMAN_PLAYER, row, col));
  }

  else if(next_mover() == COMPUTER && gameboard[row][col].get_color() == Space::AVAILABLE){
    return (look_8(COMP_PLAYER, row, col));   
  }

  else{
    return false;
  }
}

// make sure piece is within range
bool Othello::on_board(int row =0, int col=0) const{
  return (row >= 0 && row <= 7 && col >= 0 && col <= 7);
}

//push only legal moves into the queue
void Othello:: compute_moves(std::queue<string>& moves) const{
  string move = "  ";

  for( move[0] = 'A'; move[0] != 'I'; move[0]++){
    for(move[1] = '1'; move[1] != '9'; move[1]++){
      if(is_legal(move)) 
        moves.push(move);
    }
  }
}

//evaluate using a piece count and corners
int Othello::evaluate()const{

  int score =0, black = 0, white = 0;
  for (int i = 0; i < 8; ++i){
    for (int j = 0; j < 8; ++j){
      if (on_board(i, j)== true && gameboard[i][j].get_color() == Space::WHITE){
        white++;
      }
      else if (on_board(i, j) == true && gameboard[i][j].get_color() == Space::BLACK){
        black++;
      }
    }
  }

  score = black - white;
  return score;
}

//count pieces to see who is winning
game::who Othello::winning() const{
  int black_count = 0;
  int white_count = 0;
  for (int i = 0; i < 8; ++i){
    for (int j = 0; j < 8; ++j){
      if (on_board(i, j)== true && gameboard[j][i].get_color() == Space::BLACK){
        black_count++;
      }
      else if (on_board(i, j) == true && gameboard[j][i].get_color() == Space::WHITE){
        white_count++;
      }
    }
  }
  if (black_count > white_count){
    return game::HUMAN;
  }
  else if (black_count < white_count){
    return game::COMPUTER;
  }
  else{
    return game::NEUTRAL;
  }
}

//count blank squares to determine if game is done
bool Othello::is_game_over()const{
  return (passed == 2);
}