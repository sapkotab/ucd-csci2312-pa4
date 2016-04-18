//
// Created by bhuwan sapkota on 4/2/16.
//

#include "Resource.h"

using namespace Gaming;

// constant as requirement
const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;

Resource::Resource(const Game &g, const Position &p, double capacity):Piece(g,p) {
    __capacity = capacity;
}

Resource::~Resource() {

}

double Resource::consume() {
    double temp = __capacity;
    this->__capacity = 0;
    finish();
    return temp;
}

void Resource::age() {
    __capacity /=RESOURCE_SPOIL_FACTOR;
    if (__capacity < 0.001)
        __capacity = 0;
}

// if resources doen't move.
ActionType Resource::takeTurn(const Surroundings &s) const {
    return STAY;
}
//resources do not initiate interactions
Piece &Resource::operator*(Piece &other) {
    return *this;
}
//resources do not initiate interactions
Piece &Resource::interact(Agent *) {
    return *this;
}
//resources do not initiate interactions
Piece &Resource::interact(Resource *) {
    return *this;
}

