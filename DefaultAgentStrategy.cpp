//
// Created by bhuwan sapkota on 4/2/16.
//
#include "DefaultAgentStrategy.h"
using namespace Gaming;

DefaultAgentStrategy::DefaultAgentStrategy() {

}

DefaultAgentStrategy::~DefaultAgentStrategy() {

}

ActionType DefaultAgentStrategy::operator()(const Surroundings &s) const
{
    std::vector <ActionType> action = {NW,N,NE,W,STAY,E,SW,S,SE};
    std::vector <int> pieceIndex;
    int numDir=0;

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i=0; i< s.array.size(); ++i) {
        if(s.array[i]==ADVANTAGE) {
            pieceIndex.push_back(i);
            numDir++;
        }
    }
    if(numDir>0){
        std::uniform_int_distribution<> dis(0,numDir-1);
        return action[pieceIndex[dis(gen)]];
    }

    for (int i=0; i< s.array.size(); ++i) {
        if(s.array[i]==FOOD) {
            pieceIndex.push_back(i);
            numDir++;
        }
    }
    if(numDir>0){
        std::uniform_int_distribution<> dis(0,numDir-1);
        return action[pieceIndex[dis(gen)]];
    }
    for (int i=0; i< s.array.size(); ++i) {
        if(s.array[i]==EMPTY) {
            pieceIndex.push_back(i);
            numDir++;
        }
    }
    if(numDir>0){
        std::uniform_int_distribution<> dis(0,numDir-1);
        return action[pieceIndex[dis(gen)]];
    }
    for (int i=0; i< s.array.size(); ++i) {
        if(s.array[i]==SIMPLE) {
            pieceIndex.push_back(i);
            numDir++;
        }
    }
    if(numDir>0){
        std::uniform_int_distribution<> dis(0,numDir-1);
        return action[pieceIndex[dis(gen)]];
    }
    return STAY;
}

