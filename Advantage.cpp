//
// Created by bhuwan sapkota on 4/2/16.
//


#include "Advantage.h"
#include <sstream>
using namespace Gaming;

const char Advantage::ADVANTAGE_ID = 'D';
const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;

Advantage::Advantage(const Game &g, const Position &p, double capacity):Resource(g,p,capacity) {

}

Advantage::~Advantage() {

}

void Advantage::print(std::ostream &os) const {
    std::stringstream ss;
    ss << ADVANTAGE_ID << __id;
    std::string s;
    getline(ss,s);
    os << s;
}

double Advantage::getCapacity() const {
    return (__capacity*ADVANTAGE_MULT_FACTOR);
}

double Advantage::consume() {
    double temp = getCapacity();
    __capacity = 0;
    finish();
    return (temp);
}









