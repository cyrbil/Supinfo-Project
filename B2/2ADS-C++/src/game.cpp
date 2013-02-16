#include "../include/game.h"

// Constructor
game::game(unsigned int w, unsigned int h, std::string player1, std::string player2){
    _board = new board(w,h);
    players[0] = player(_board->Get_width()/2-1, _board->Get_height()/2, player1);
    players[1] = player(_board->Get_width()/2, _board->Get_height()/2, player2);
    winner = "";
    ended = false;
}
// Destructor
game::~game(){ delete players; }
// Copy Constructor
game::game(const game& other){
    players[0] = player(other.players[0]);
    players[1] = player(other.players[1]);
    _board = new board(other._board->Get_width(),other._board->Get_height());
    winner = other.winner;
    ended = other.ended;
}
