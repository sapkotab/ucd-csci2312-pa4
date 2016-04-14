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
    double temp = getCapacity();
    this->__capacity = 0;
    finish();
    return temp;
}

void Resource::age() {
    __capacity -=RESOURCE_SPOIL_FACTOR;   // TODO if we divide they are never goona age.
}

// if resource doesn't move why it would interact with anyone?
// all of the follow should be just a tricky implementation

ActionType Resource::takeTurn(const Surroundings &s) const {
    return STAY;
}

Piece &Resource::operator*(Piece &other) {
    return *this;
}

Piece &Resource::interact(Agent *) {
    return *this;
}

Piece &Resource::interact(Resource *) {
    return *this;
}

