//
// Created by bhuwan sapkota on 4/2/16.
//


#include "Advantage.h"
#include <iomanip>
using namespace Gaming;

const char Advantage::ADVANTAGE_ID = 'D';
const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;

Advantage::Advantage(const Game &g, const Position &p, double capacity):Resource(g,p,capacity) {

}

Advantage::~Advantage() {

}

void Advantage::print(std::ostream &os) const {
    os << ADVANTAGE_ID << __id ;
}

double Advantage::getCapacity() const {
    return (__capacity*ADVANTAGE_MULT_FACTOR);
}

double Advantage::consume() {
    double temp = getCapacity();
    this->__capacity = 0;
    finish();
    return temp;
}









