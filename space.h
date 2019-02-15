/******************************************************************
    This is the header for a single space of an Othello board
    Luke Putz           Fall 2016
**********************************************************************/
#ifndef SPACE_H
#define SPACE_H

#include <iostream>
#include <string>
    
class Space {   
  public:
    enum color {BLACK, WHITE, AVAILABLE};    
  
    Space();
    std::ostream& output()const;

    //mutators
    void place_black();
    void place_white();
    void flip(); 
    void set_color(const color& c);
    bool operator ==(const color& other)const;
    bool operator !=(const color& other) const;


     //getters
    color get_color() const{ return spacecolor; }
    void display_available() const;
    void display_piece(std::string color) const;

  private:
    color spacecolor;

 };
   

#endif
