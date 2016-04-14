//
// Created by bhuwan sapkota on 4/2/16.
//


#include "Strategic.h"
#include <iomanip>
using namespace Gaming;

const char Strategic::STRATEGIC_ID = 'T';

Strategic::Strategic(const Game &g, const Position &p, double energy, Strategy *s):Agent(g,p,energy) {
    __strategy = s;
}

Strategic::~Strategic() {
    delete __strategy;
}

void Strategic::print(std::ostream &os) const {
    os << STRATEGIC_ID << __id;
}

ActionType Strategic::takeTurn(const Surroundings &s) const {
    for (int i = s.array.size()-1; i >= 0; --i) {
        if(s.array[i]==ADVANTAGE)
            return ActionType(i);
    }
    for (int i = s.array.size()-1; i >= 0; --i) {
        if(s.array[i]==FOOD)
            return ActionType(i);
    }
    for (int i = s.array.size()-1; i >= 0; --i) {
        if(s.array[i]==EMPTY)
            return ActionType(i);
    }
    for (int i = s.array.size()-1; i >= 0; --i) {
        if(s.array[i]==SIMPLE)
            return ActionType(i);
    }
    return STAY;
}







