//
// Created by bhuwan sapkota on 4/2/16.
//

#include "Food.h"
#include <sstream>
using namespace Gaming;

const char Food::FOOD_ID = 'F';
Food::Food(const Game &g, const Position &p, double capacity):Resource(g,p,capacity) {
    // no extra members
}

Food::~Food() {
    // nothing to deallocate.
}

void Food::print(std::ostream &os) const {
    // ss has two chunk stream
    // need to combine two stream to make it one before return
    // otherwise setw(5) will not work in game "<<" overloading.
    // it only give five space for ID.
    std::stringstream ss;
    ss << FOOD_ID << __id;
    std::string s;
    getline(ss,s);
    os << s;
}





