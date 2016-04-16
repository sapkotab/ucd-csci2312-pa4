//
// Created by bhuwan sapkota on 4/2/16.
//
#include "AggressiveAgentStrategy.h"
#include "Game.h"
using namespace Gaming;


const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY* 0.75;

AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy) {
    __agentEnergy = agentEnergy;
}

AggressiveAgentStrategy::~AggressiveAgentStrategy() {

}


ActionType AggressiveAgentStrategy::operator()(const Surroundings &s) const{

    std::vector <ActionType> action = {NW,N,NE,W,STAY,E,SW,S,SE};
    std::vector <int> pieceIndex;
    int numDir=0;

    std::random_device rd;
    std::mt19937 gen(rd());

    if(__agentEnergy >= DEFAULT_AGGRESSION_THRESHOLD) {
        for (int i=0; i< s.array.size(); ++i) {
            if(s.array[i]==SIMPLE || s.array[i]==STRATEGIC) {
                pieceIndex.push_back(i);
                numDir++;
            }
        }
        if(numDir>0){
            std::uniform_int_distribution<> dis(0,numDir-1);
            return action[pieceIndex[dis(gen)]];
        }

//        for (int i=0; i< s.array.size(); ++i) {
//            if(s.array[i]==STRATEGIC) {
//                pieceIndex.push_back(i);
//                numDir++;
//            }
//        }
//        if(numDir>0){
//            std::uniform_int_distribution<> dis(0,numDir-1);
//            return action[pieceIndex[dis(gen)]];
//        }
    }
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
    return STAY;

}
