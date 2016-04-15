//
// Created by bhuwan sapkota on 4/2/16.
//

#include "Food.h"
#include <sstream>
using namespace Gaming;

const char Food::FOOD_ID = 'F';
Food::Food(const Game &g, const Position &p, double capacity):Resource(g,p,capacity) {

}

Food::~Food() {

}

void Food::print(std::ostream &os) const {

    std::stringstream ss;
    ss << FOOD_ID << __id;
    std::string s;
    getline(ss,s);
    os << s;
}





