#ifndef PIECE_H
#define PIECE_H

class piece
{
    private:
        unsigned int _x, _y;
    public:
        // Constructor
        piece(unsigned int x = 0, unsigned int y = 0);
        // Setters/Getters
        unsigned int Get_x();
        void Set_x(unsigned int);
        unsigned int Get_y();
        void Set_y(unsigned int);
};

#endif // PIECE_H
