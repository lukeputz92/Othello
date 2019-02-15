/******************************************************************
    This is the implementation for a single space of an Othello board
    Luke Putz           Fall 2016
**********************************************************************/
#include "space.h"
#include "colors.h"
#include <string>

Space::Space() {
  spacecolor = AVAILABLE;
}

//puts black piece on by changing spacecolor
void Space::place_black(){
  if (spacecolor == AVAILABLE){
    spacecolor = BLACK;
  }
  else{
    return;
  }
}

// puts white piece on by changing spacecolor
void Space::place_white(){
  if (spacecolor == AVAILABLE){
    spacecolor = WHITE;
  }
  else{
    return;
  }
}
//checks colors flips accordingly
void Space::flip(){
  if (spacecolor == BLACK){
    spacecolor = WHITE;
  }
  else if (spacecolor == WHITE){
    spacecolor = BLACK;
  }
  else{
    return;
  }
}
//setter
void Space::set_color(const Space::color& c){
  spacecolor = c;
}
//displays according to color
std::ostream& Space::output()const {
  if (spacecolor == AVAILABLE){
    display_available();
  }
  else if (spacecolor == BLACK || spacecolor == WHITE){
    if (spacecolor == BLACK){
      display_piece("black");
    } 
    else if (spacecolor == WHITE){
      display_piece("white");
    } 
  }             
  return std::cout;
}
//display function for blank spaces
void Space::display_available() const{
  std::cout << B_GREEN << "       " << RESET;
}
//display function for colors matched by string
void Space::display_piece(std::string c) const {
  if (c == "black")
    std::cout << B_BLACK << "       " << RESET;
  else if (c == "white")
    std::cout << B_WHITE << "       " << RESET;  
} 

bool Space::operator ==(const Space::color& other)const{
  if(spacecolor == other) return true;
  else
    return false;
}
bool Space::operator !=(const Space::color& other)const{
  if(spacecolor != other) return true;
  else
    return false;
}



