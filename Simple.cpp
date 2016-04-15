//
// Created by bhuwan sapkota on 4/2/16.
//


#include "Simple.h"
#include <sstream>
using namespace Gaming;

const char Simple::SIMPLE_ID = 'S';

Simple::Simple(const Game &g, const Position &p, double energy):Agent(g,p,energy) {

}

Simple::~Simple() {

}

void Simple::print(std::ostream &os) const {
    std::stringstream ss;
    ss << SIMPLE_ID << __id;
    std::string s;
    getline(ss,s);
    os << s;
}

ActionType Simple::takeTurn(const Surroundings &s) const {

    std::vector <ActionType> action = {NW,N,NE,W,STAY,E,SW,S,SE};
    std::vector <int> pieceIndex;

    for (int i=0; i< s.array.size(); ++i) {
        if(s.array[i]==FOOD|| s.array[i]==ADVANTAGE) {
            pieceIndex.push_back(i);
        }
    }
    if(pieceIndex.size()>0){
        PositionRandomizer p;
        Position ps = p(pieceIndex);
        return action[(ps.x*3 + ps.y)];
    }

    for (int i=0; i< s.array.size(); ++i) {
        if(s.array[i]==EMPTY)
            pieceIndex.push_back(i);
    }
    if(pieceIndex.size()>0){
        PositionRandomizer p;
        Position ps = p(pieceIndex);
        return action[(ps.x*3 + ps.y)];
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

