#include "../include/player.h"


unsigned int abs(int number){ return (unsigned int) (number >= 0) ? number : -number; }

/* // Non herited class constructor
// Constructor
player::player(unsigned int x, unsigned int y, std::string name){
    _piece = piece(x,y);
    _pseudo = name;
}
//*/

// herited class constructor
player::player(unsigned int x, unsigned int y, std::string name, std::string lastname){
    _piece = piece(x,y);
    _pseudo = name;

    // people's attributes
    _firstname = name;
    _lastname = lastname;
}


void player::move(board& _board){
    unsigned int x,y;
    unsigned int player_x = _piece.Get_x();
    unsigned int player_y = _piece.Get_y();
    if(!can_move(_board)){
        cout << "Can't move" << endl;
        return;
    }
    cout << "\""<< _pseudo << "\" please choose where to move:" << endl;
    do{
        cout << "\tRow number: ";
        cin >> x;
        cout << "\tColumn number: ";
        cin >> y;
        if(!_board.is_free(x,y))
            cout << "\nSquare is not free." <<endl;
        // square is reachable if distance from x or y is less than 2
        else if(abs((int)(player_x-x))>1 || abs((int)(player_y-y))>1)
            cout << "\nSquare is not reachable." << endl;

    }while(!_board.is_free(x,y) ||      // reprompt while player does bad choices
           abs((int)(player_x-x))>1 ||
           abs((int)(player_y-y))>1);

    cout << "Moving to: (" << x << "," << y << ")" << endl;
    _board.set_square(x,y,_board.get_square(player_x,player_y)); // copy piece into new position
    _board.set_square(player_x,player_y,0);                      // delete old position
    _piece.Set_x(x);  _piece.Set_y(y);                           // update piece coord
}

void player::drop_wall(board& _board){
    unsigned int x,y;

    cout << _pseudo << " please choose where to drop a wall:" << endl;
    do{
        cout << "\tRow number: ";
        cin >> x;
        cout << "\tColumn number: ";
        cin >> y;
        if(!_board.is_free(x,y))
            cout << "\nSquare is not free." <<endl;
    }while(!_board.is_free(x,y)); // reprompt while player does bad choices

    cout << "Droping wall into: (" << x << "," << y << ")" << endl;
    _board.set_square(x,y,3); // drop a wall
}

bool player::can_move(board& _board){
    int x = (int)_piece.Get_x();
    int y = (int)_piece.Get_y();
    int w = (int)_board.Get_width();
    int h = (int)_board.Get_height();

    // look around piece,
    // if one free square, return true.
    for(int i=-1; i<2;i++)
        for(int j=-1; j<2;j++)
            if(x+i>-1&&y+j>-1&&x+i<w&&y+j<h)
                if(_board.is_free(x+i,y+j)) return true;
    return false;
}
