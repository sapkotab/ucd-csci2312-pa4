//
// Created by bhuwan sapkota on 4/2/16.
//

#include "Piece.h"

using namespace Gaming;

unsigned int Piece::__idGen = 1;

Piece::Piece(const Game &g, const Position &p):__game(g) {
    __id = __idGen;
    __idGen++; // increment so it will be ready for next one.
    __finished = false; // initially not finishend
    __turned = false;
    __position = p;

}

Piece::~Piece() {
// nothing to delete
}

std::ostream & Gaming::operator<<(std::ostream &os, const Piece &piece) {
    piece.print(os);
    return os;
}





