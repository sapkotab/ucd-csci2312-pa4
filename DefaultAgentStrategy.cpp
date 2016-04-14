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
    for (int i = s.array.size()-1; i >= 0; --i) {
        if(s.array[i]==SIMPLE)
            return ActionType(i);
    }
    return STAY;
}

