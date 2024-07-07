#include "position.h"

Position::Position() :
    x_(0),
    y_(0)
{
}
Position::Position(int x, int y) :
    x_(x),
    y_(y)
{
}

Position::Position(const Position& other) {
    if (this != &other) {
        x_ = other.x_;
        y_ = other.y_;
    }
}

Position& Position::operator=(const Position& other) {
    if (this != &other) {
        x_ = other.x_;
        y_ = other.y_;
    }
    return *this;
}

void Position::setPosition(int x, int y) {
    x_ = x;
    y_ = y;
}

int Position::getX() {
    return x_;
}
int Position::getY() {
    return y_;
}


