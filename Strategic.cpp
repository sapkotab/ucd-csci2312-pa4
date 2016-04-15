//
// Created by bhuwan sapkota on 4/2/16.
//


#include "Strategic.h"
#include <sstream>
using namespace Gaming;

const char Strategic::STRATEGIC_ID = 'T';

Strategic::Strategic(const Game &g, const Position &p, double energy, Strategy *s):Agent(g,p,energy) {
    __strategy = s;
}

Strategic::~Strategic() {
    delete __strategy;
}

void Strategic::print(std::ostream &os) const {
    std::stringstream ss;
    ss << STRATEGIC_ID << __id;
    std::string s;
    getline(ss,s);
    os << s;
}

ActionType Strategic::takeTurn(const Surroundings &s) const {
    return (*this->__strategy)(s);

}







