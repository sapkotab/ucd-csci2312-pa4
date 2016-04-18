//
// Created by bhuwan sapkota on 4/2/16.
//


#include "Agent.h"
#include "Food.h"


using namespace Gaming;

const double Agent::AGENT_FATIGUE_RATE = 0.3;   // for age()

Agent::Agent(const Game &g, const Position &p, double energy):Piece(g,p) {
    __energy = energy; // energy is only extra member on derived class.
}

Agent::~Agent() {

}

void Agent::age() {
    __energy -=AGENT_FATIGUE_RATE; // age by this every round of game
}

Piece &Agent::operator*(Piece &other) {

    // finding what exactly &other is by casting it to derived classes
    // whichever is true will be executed on runtime.

    Agent *otherAgent = dynamic_cast<Agent*>(&other);
    if(otherAgent)  // otherAgent will be valid if passed Piece is agent.
        return interact(otherAgent);

    Resource *resource = dynamic_cast<Resource*>(&other);
    if(resource)// resource will be valid if passed Piece is resource.
        return  interact(resource);
    return *this;
}

Piece &Agent::interact(Agent * other) {

    // whichever has more energy live and other one will become unViable through finish()
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
        // if both have same energy both will become unViable through finish()
    else{
        __energy = 0.0;
        other->__energy = 0.0;
        finish();
        other->finish();
    }
    return *this;
}

Piece &Agent::interact(Resource * other) {

    // consumes resource and increase energy
    // resource will become unViable through consume()
    this->addEnergy(other->consume());

    return *this;
}
