#include "../include/piece.h"

// Constructor
piece::piece(unsigned int x, unsigned int y)
{ _x = x; _y = y; }

// Setters/Getters
unsigned int piece::Get_x() { return _x; }
void piece::Set_x(unsigned int val) { _x = val; }
unsigned int piece::Get_y() { return _y; }
void piece::Set_y(unsigned int val) { _y = val; }
