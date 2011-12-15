#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "../include/piece.h"
#include "../include/board.h"
#include "../include/people.h"

using namespace std;


//class player
class player : public people
{
    private:
        piece _piece;
        std::string _pseudo;
    public:
        //player(unsigned int x = 0, unsigned int y = 0, std::string name = "Cyrbil");                           // Non herited class constructor
        player(unsigned int x = 0, unsigned int y = 0, std::string name = "John", std::string lastname = "Doe"); // herited class constructor

        // look around piece, return if there is or not a movement possibility
        bool can_move(board&);
        // prompt and move player piece
        void move(board&);
        // prompt and drop a wall
        void drop_wall(board&);
        // return pseudo
        //std::string Get_pseudo(void) { return _pseudo; }
        std::string Get_pseudo(void) { return Get_firstname()+" "+Get_lastname(); }
};

#endif // PLAYER_H
