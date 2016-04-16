//
// Created by bhuwan sapkota on 4/2/16.
//


#include "Agent.h"
#include "Food.h"
#include "Advantage.h"
#include "Strategic.h"

using namespace Gaming;

const double Agent::AGENT_FATIGUE_RATE = 0.3;

Agent::Agent(const Game &g, const Position &p, double energy):Piece(g,p) {
    __energy = energy;
}

Agent::~Agent() {

}

void Agent::age() {
    __energy -=AGENT_FATIGUE_RATE;
}

Piece &Agent::operator*(Piece &other) {
    Agent *otherAgent = dynamic_cast<Agent*>(&other);
    if(otherAgent)
        return this->interact(otherAgent);

    Resource *resource = dynamic_cast<Resource*>(&other);
    if(resource)
        return  this->interact(resource);
    return *this;
}

Piece &Agent::interact(Agent * other) {
    // whichever has more energy live
    if(__energy > other->__energy){
        __energy -=other->__energy;
        other->__energy = 0;
        other->finish();
    }
    else if (__energy < other->__energy){
        other->__energy -=__energy;
        __energy=0;
        finish();
    }
        // if both have same energy both will die.
    else{
        __energy = 0.0;
        other->__energy = 0.0;
        finish();
        other->finish();
    }
    return *this;
}

Piece &Agent::interact(Resource * other) {

    this->addEnergy(other->consume());

    return *this;
}
