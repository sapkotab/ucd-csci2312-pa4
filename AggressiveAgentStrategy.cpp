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

    if(this->__agentEnergy >= DEFAULT_AGGRESSION_THRESHOLD) {
        for (int i=0; i< s.array.size(); ++i) {
            if(s.array[i]==SIMPLE){
                pieceIndex.push_back(i);
            }

        }
        if(pieceIndex.size()>0){
            PositionRandomizer p;
            Position ps = p(pieceIndex);
            return action[(ps.x*3 + ps.y)];
        }

        for (int i=0; i< s.array.size(); ++i) {
            if(s.array[i]==STRATEGIC){
                pieceIndex.push_back(i);
            }

        }
        if(pieceIndex.size()>0){
            PositionRandomizer p;
            Position ps = p(pieceIndex);
            return action[(ps.x*3 + ps.y)];
        }
    }
    for (int i=0; i< s.array.size(); ++i) {
        if(s.array[i]==ADVANTAGE){
            pieceIndex.push_back(i);
        }

    }
    if(pieceIndex.size()>0){
        PositionRandomizer p;
        Position ps = p(pieceIndex);
        return action[(ps.x*3 + ps.y)];
    }

    for (int i=0; i< s.array.size(); ++i) {
        if(s.array[i]==FOOD){
            pieceIndex.push_back(i);
        }

    }
    if(pieceIndex.size()>0){
        PositionRandomizer p;
        Position ps = p(pieceIndex);
        return action[(ps.x*3 + ps.y)];
    }
    for (int i=0; i< s.array.size(); ++i) {
        if(s.array[i]==EMPTY){
            pieceIndex.push_back(i);
        }

    }
    if(pieceIndex.size()>0){
        PositionRandomizer p;
        Position ps = p(pieceIndex);
        return action[(ps.x*3 + ps.y)];
    }
    return STAY;

}
