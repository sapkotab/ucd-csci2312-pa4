//
// Created by bhuwan sapkota on 4/2/16.
//


#include "Advantage.h"
#include <sstream>
using namespace Gaming;

const char Advantage::ADVANTAGE_ID = 'D';
const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;

Advantage::Advantage(const Game &g, const Position &p, double capacity):Resource(g,p,capacity) {
    // no extra variables
}

Advantage::~Advantage() {
    // nothing to deallocate.
}

void Advantage::print(std::ostream &os) const {

    std::stringstream ss;
    ss << ADVANTAGE_ID << __id; // ss has two chunk stream
    std::string s;
    getline(ss,s);              // combining two stream to make it one.
    os << s;
}

double Advantage::getCapacity() const {
    return (__capacity*ADVANTAGE_MULT_FACTOR);  // advantage has more capacity for consumer not for itself
}

double Advantage::consume() {
    // if consumed make its only capacity to zero and return double getCapacity()
    double temp = getCapacity();
    __capacity = 0;
    finish();
    return (temp);
}









