//
// Created by bhuwan sapkota on 4/2/16.
//

#include "Food.h"
#include <iomanip>
using namespace Gaming;

const char Food::FOOD_ID = 'F';
Food::Food(const Game &g, const Position &p, double capacity):Resource(g,p,capacity) {

}

Food::~Food() {

}

void Food::print(std::ostream &os) const {
    os << FOOD_ID << __id;
}





