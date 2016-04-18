//
// Created by bhuwan sapkota on 4/2/16.
//
#include "AggressiveAgentStrategy.h"
#include "Game.h"
using namespace Gaming;

// this will decide the agent will be aggressive or not.
const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY* 0.75;

AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy) {
    __agentEnergy = agentEnergy;                // need to be syncing to the called Strategic object energy
}

AggressiveAgentStrategy::~AggressiveAgentStrategy() {
    // nothing to deallocate
}


ActionType AggressiveAgentStrategy::operator()(const Surroundings &s) const{

    std::vector <ActionType> action = {NW,N,NE,W,STAY,E,SW,S,SE}; // direction vector to return

    // vector that contain all possible position.
    std::vector<int> positions;
    for (int i = 0; i < 4; i++) positions.push_back(i);
    for (int i = 5; i < 9; i++) positions.push_back(i);
    // if surrounding position is filled with what it is looking for will turn true
    bool found = false;

    if(__agentEnergy >= DEFAULT_AGGRESSION_THRESHOLD) {
        for (int i=0; i< s.array.size(); ++i) {
            if(s.array[i]==SIMPLE|| s.array[i]==STRATEGIC) {
                found = true;
                break;
            }
        }
        if (found){// if found.
            while (true) {  // since we know it is in there keep generating new random position
                Position position = Game::randomPosition(positions);
                if (s.array[position.x * 3 + position.y] == SIMPLE ||s.array[position.x * 3 + position.y] == STRATEGIC) {
                    return action[position.x * 3 + position.y];
                }
            }
        }

    }
    // same as above..
    for (int i=0; i< s.array.size(); ++i) {
        if(s.array[i]==ADVANTAGE) {
            found = true;
            break;
        }
    }
    if(found){
        while (true) {
            Position position = Game::randomPosition(positions);
            if (s.array[position.x * 3 + position.y] == ADVANTAGE) {
                return action[position.x * 3 + position.y];
            }
        }
    }

    for (int i=0; i< s.array.size(); ++i) {
        if(s.array[i]==FOOD|| s.array[i]==ADVANTAGE) {
            found = true;
            break;
        }
    }
    if(found){
        while (true) {
            Position position = Game::randomPosition(positions);
            if (s.array[position.x * 3 + position.y] == FOOD ||s.array[position.x * 3 + position.y] == ADVANTAGE) {
                return action[position.x * 3 + position.y];
            }
        }
    }
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
