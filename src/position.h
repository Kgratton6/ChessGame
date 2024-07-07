#ifndef POSITION_H
#define POSITION_H

// Classe qui à pour but de representer la position d'une pièce sur l'échéquier.
// La position (0, 0) indique la base a1

class  Position
{
public:
    // Constructeurs
    Position();
    Position(int x, int y);
    ~Position() = default;

     // operations de copie :
    Position(const Position& other);
    Position& operator=(const Position& other);

    void setPosition(int x, int y);

    int getX();
    int getY();

private:
    int x_;
    int y_;
};

#endif // POSITION_H
