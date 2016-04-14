//
// Created by bhuwan sapkota on 4/2/16.
//


#include "Simple.h"
#include <iomanip>
using namespace Gaming;

const char Simple::SIMPLE_ID = 'S';

Simple::Simple(const Game &g, const Position &p, double energy):Agent(g,p,energy) {

}

Simple::~Simple() {

}

void Simple::print(std::ostream &os) const {
    os << SIMPLE_ID <<__id ;
}

ActionType Simple::takeTurn(const Surroundings &s) const {
    // temp solution until randomization work
    for (int i = s.array.size()-1; i >= 0; --i) {
        if(s.array[i]==FOOD|| s.array[i]==ADVANTAGE)
            return ActionType(i);
    }

    for (int i = s.array.size()-1; i >= 0; --i) {
        if(s.array[i]==EMPTY)
            return ActionType(i);
    }
    return STAY;



//    // declaring and filling the temp array with for randomizer
//    std::vector <int> temp;
//    for (int i = 0; i < s.array.size(); ++i) {
//        temp[i] = i;
//    }
//        PositionRandomizer PR;
//    for (int j = 0; j < s.array.size(); ++j) {
//        Position p = PR(temp);          // random position
//        int position = ((p.x)*3)+(p.y); // random index based on position
//        if (s.array[position] == FOOD ||s.array[position] == ADVANTAGE)
//            return ActionType(position);
//    }
//
//    // if it didn't find the food, it goes to look for Empty
//    for (int j = 0; j < s.array.size(); ++j) {
//        Position p = PR(temp);          // random position
//        int position = ((p.x)*3)+(p.y); // random index based on position
//        if (s.array[position] == EMPTY)
//            return ActionType(position);
//    }
//    // last resort stay put
//    return STAY;
}

