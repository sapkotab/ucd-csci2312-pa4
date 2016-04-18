//
// Created by bhuwan sapkota on 4/2/16.
//


#include "Simple.h"
#include <sstream>


using namespace Gaming;

const char Simple::SIMPLE_ID = 'S';

Simple::Simple(const Game &g, const Position &p, double energy):Agent(g,p,energy) {
    // no extra member variables
}

Simple::~Simple() {
    //nothing to deallocate.
}

void Simple::print(std::ostream &os) const {
    // ss has two chunk stream
    // need to combine two stream to make it one before return
    // otherwise setw(5) will not work in game "<<" overloading.
    // it only give five space for ID.
    std::stringstream ss;
    ss << SIMPLE_ID << __id;
    std::string s;
    getline(ss,s);
    os << s;
}

ActionType Simple::takeTurn(const Surroundings &s) const {

    std::vector <ActionType> action = {NW,N,NE,W,STAY,E,SW,S,SE}; // direction vector for returning

    // vector that contain all possible position.
    std::vector<int> positions;
    for (int i = 0; i < 4; i++) positions.push_back(i);
    for (int i = 5; i < 9; i++) positions.push_back(i);

    // if surrounding position is filled with what it is looking for will turn true
    bool found = false;

    for (int i=0; i< s.array.size(); ++i) {
        if(s.array[i]==FOOD|| s.array[i]==ADVANTAGE) {
            found = true;
            break;
        }
    }
    if(found) {  // if found.
        while (true) {  // since we know it is in there keep generating new random position
            Position position = Game::randomPosition(positions);
            if (s.array[position.x * 3 + position.y] == FOOD || s.array[position.x * 3 + position.y] == ADVANTAGE) {
                return action[position.x * 3 + position.y];
            }
        }
    }

    // same condition applied

    for (int i=0; i< s.array.size(); ++i) {
        if(s.array[i]==EMPTY) {
            found = true;
            break;
        }
    }
    if(found){
        while (true) {
            Position position = Game::randomPosition(positions);
            if (s.array[position.x * 3 + position.y] == EMPTY) {
                return action[position.x * 3 + position.y];
            }
        }
    }


    // if nothing possible just stay
    return STAY;

}

