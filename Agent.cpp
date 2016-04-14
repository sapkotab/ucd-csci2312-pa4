//
// Created by bhuwan sapkota on 4/2/16.
//


#include "Agent.h"
#include "Food.h"
#include "Advantage.h"

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
    return other.interact(this);
}

Piece &Agent::interact(Agent * other) {
    // whichever has more energy live
    if(this->__energy > other->__energy){
        this->__energy -=other->__energy;
        other->finish();
    }
    else if (other->__energy > this->__energy){
        other->__energy-=this->__energy;
        this->finish();
    }
        // if both have same energy both will die.
    else {
        this->__energy = other->__energy = 0;
        this->finish();
        other->finish();
    }
    return *this;
}

Piece &Agent::interact(Resource * other) {

    this->addEnergy(other->consume());

//    Resource *resrce = dynamic_cast<Food*>(other); // casting to real class
//    if (resrce) {
//        this->addEnergy(resrce->consume());
//    }
//
//        resrce = dynamic_cast<Advantage*>(other); // casting to real class
//    if (resrce->getType()==ADVANTAGE) {
//        this->addEnergy(resrce->consume());
//    }

    return *this;
}
