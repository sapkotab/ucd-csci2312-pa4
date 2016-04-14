//
// Created by bhuwan sapkota on 4/2/16.
//
#include "AggressiveAgentStrategy.h"
using namespace Gaming;


const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = 20 * 0.75; // TODO Game::STARTING_AGENT_ENERGY instead 20

AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy) {
    __agentEnergy = agentEnergy;
}

AggressiveAgentStrategy::~AggressiveAgentStrategy() {

}


ActionType AggressiveAgentStrategy::operator()(const Surroundings &s) const{
    if(__agentEnergy >=DEFAULT_AGGRESSION_THRESHOLD) {
        for (int i = s.array.size() - 1; i >= 0; --i) {
            if (s.array[i] == STRATEGIC || s.array[i]==SIMPLE)
                return ActionType(i);
        }
    }

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
    return STAY;

}
