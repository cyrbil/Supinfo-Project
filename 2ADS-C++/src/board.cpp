#include <iostream>
#include "../include/board.h"

using namespace std;

// templates used to alloc and free dynamic array (board)
template <typename T>
T **AllocateDynamicArray( int nRows, int nCols){
      T **dynamicArray;

      dynamicArray = new T*[nRows]; // alloc rows
      for( int i = 0 ; i < nRows ; i++ )
        dynamicArray[i] = new T [nCols]; // alloc cols

      return dynamicArray;
}
template <typename T>
void FreeDynamicArray(T** dArray){
      delete [] *dArray; // free cols
      delete [] dArray;  // free rows
}



// Constructor
board::board(unsigned int width, unsigned int height) {
    if(width<4 || width%2 != 0) // minimum width size 4
        width = 6;
    if(height<3 || height%2 != 1)// minimum height size 3
        height = 5;

    _width = width;
    _height = height;

    // alloc board
    _board = AllocateDynamicArray<unsigned int>(width,height);
    // fill with 0
    for(unsigned int x=0U; x<width;++x)
        for(unsigned int y=0U; y<height;++y)
            _board[x][y] = 0;

    // put player one on board
    _board[width/2-1][height/2] = 1;
    // put player two on board
    _board[width/2][height/2] = 2;

}
// Copy Constructor
board::board(const board& _class) {
    // simply copy attributes
    _width = _class._width;
    _height = _class._height;
    // create a new two-dimension array
    // alloc board
    _board = AllocateDynamicArray<unsigned int>(_width,_height);
    // fill with values of copied board
    for(unsigned int x=0U; x<_width;++x)
        for(unsigned int y=0U; y<_height;++y)
            _board[x][y] = _class._board[x][y];

}
// Destructor
board::~board() {
    FreeDynamicArray<unsigned int>(_board);
}
// Affectation Operator
board* board::operator++(int _class) {
    unsigned int new_width = _width + 2;
    unsigned int new_height = _height + 2;
    // alloc new board
    unsigned int** new_board = AllocateDynamicArray<unsigned int>(new_width,new_height);
    // copy board or add 0
    for(unsigned int x=0U; x<new_width;++x)
        for(unsigned int y=0U; y<new_height;++y)
            if(x<_width && y<_height)
                new_board[x][y] = _board[x][y];
            else
                new_board[x][y] = 0;
    // finally replace class board
    _board = new_board;
    _width = new_width;
    _height = new_height;
    return this;
}

// Know if a square is occupied (by wall or player)
// return true (free) or false (occupied)
bool board::is_free(unsigned int x, unsigned y){ return (x<_width&&y<_height)?(_board[x][y]==0)?true:false:false;}
// Display actual state of board
void board::display(void){
    string out = "";
    for(unsigned int y=0U;y<_height;++y){
        for(unsigned int x=0U;x<_width;++x){
            switch(_board[x][y]){
                case 0:
                    out += ".";
                    break;
                case 1:
                    out += "X";
                    break;
                case 2:
                    out += "0";
                    break;
                default:
                    out += "B";
            }
        }
        out += "\n";
    }
    cout << out;
}
// Return value of square or -1 if out of board
int  board::get_square(unsigned int x, unsigned int y){ return (x<_width&&y<_height)?_board[x][y]:-1; }
// Set square if in board
void board::set_square(unsigned int x, unsigned int y, unsigned int value){ if(x<_width&&y<_height&&value<4) _board[x][y]=value; }

