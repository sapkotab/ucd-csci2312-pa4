//
// Created by bhuwan sapkota on 4/2/16.
//
#include "Game.h"
//TODO I don't want them in here.
#include "Simple.h"
#include "Strategic.h"
#include "Advantage.h"
#include "Food.h"


using namespace Gaming;

// given constacts // requirements

const unsigned  int Game::NUM_INIT_AGENT_FACTOR = 4;
const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;

const unsigned int Game::MIN_WIDTH = 3;
const unsigned int Game::MIN_HEIGHT = 3;
const double Game::STARTING_AGENT_ENERGY = 20;
const double Game::STARTING_RESOURCE_CAPACITY = 10;

// automatic populator of grid.
void Game::populate() {

    // constanct requiremnts
    __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
    __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
    unsigned int numStrategic = __numInitAgents / 2;
    unsigned int numSimple = __numInitAgents - numStrategic;
    unsigned int numAdvantages = __numInitResources / 4;
    unsigned int numFoods = __numInitResources - numAdvantages;

    // simple pseudo-random number generator
// sufficient for our casual purposes
    std::default_random_engine gen;
    std::uniform_int_distribution<int> d(0, __width * __height-1); // this is the range of int that will be


// populate Strategic agents
    while (numStrategic > 0) {
        int i = d(gen); // random index in the grid vector
        if (__grid[i] == nullptr) { // is position empty
            Position pos(i / __width, i % __width);
            __grid[i] = new Strategic(*this, pos, STARTING_AGENT_ENERGY);
            numStrategic --;
        }
    }

    while (numSimple > 0) {
        int i = d(gen); // random index in the grid vector
        if (__grid[i] == nullptr) { // is position empty
            Position pos(i / __width, i % __width);
            __grid[i] = new Simple(*this, pos, STARTING_AGENT_ENERGY);
            numSimple --;
        }
    }
    while (numAdvantages > 0) {
        int i = d(gen); // random index in the grid vector
        if (__grid[i] == nullptr) { // is position empty
            Position pos(i / __width, i % __width);
            __grid[i] = new Advantage(*this, pos, STARTING_RESOURCE_CAPACITY);
            numAdvantages --;
        }
    }
    while (numFoods > 0) {
        int i = d(gen); // random index in the grid vector
        if (__grid[i] == nullptr) { // is position empty
            Position pos(i / __width, i % __width);
            __grid[i] = new Food(*this, pos, STARTING_RESOURCE_CAPACITY);
            numFoods --;
        }
    }

}

Game::Game() {
    __width = 3;
    __height = 3;
    __round = 0;
    __status = NOT_STARTED ;
    __verbose = false;
    for (int i = 0; i < __width*__height; ++i) {
        __grid.push_back(nullptr) ;
    }

}

Game::Game(unsigned width, unsigned height, bool manual) {
    if(width < MIN_WIDTH || height < MIN_HEIGHT) throw InsufficientDimensionsEx(MIN_WIDTH,MIN_HEIGHT,width,height);
    __width = width;
    __height = height;
    __verbose = false;
    __status = NOT_STARTED;
    __round = 0;
    for (int i = 0; i < __width*__height; ++i) {
        __grid.push_back(nullptr) ;
    }
    if(!manual)
        populate();
}

//Game::Game(const Game &another) {
//
//    __width = another.__width;
//    __height = another.__height;
//    __verbose = another.__verbose;
//    __round = another.__round;
//    __status = another.__status;
//    for (int i = 0; i < another.__grid.size(); ++i) {
//      __grid[i]= another.__grid[i]; // may need to use new operator?
//    }
//}

Game::~Game() { // deleting all the grids if they are filled.
    for (int i = 0; i < __grid.size(); ++i) {
       if (__grid[i] != nullptr)
           delete __grid[i];
    }
}

unsigned int Game::getNumPieces() const {
    return getNumAgents()+getNumResources();
}

unsigned int Game::getNumAgents() const {
    return getNumSimple()+getNumStrategic();
}

unsigned int Game::getNumSimple() const {
    unsigned int s =0;
    for (int i = 0; i < __grid.size(); ++i) {
        if(__grid[i]!= nullptr) {
            if (__grid[i]->getType() == SIMPLE)
                s++;
        }
    }
    return s;
}

unsigned int Game::getNumStrategic() const {
    unsigned int t=0;
    for (int i = 0; i < __grid.size(); ++i) {
        if(__grid[i]!= nullptr) {
            if (__grid[i]->getType() == STRATEGIC)
                t++;
        }
    }
    return t;
}

unsigned int Game::getNumResources() const {
    unsigned int r=0;

    for (int i = 0; i < __grid.size(); ++i) {
        if(__grid[i]!= nullptr) {
            if (__grid[i]->getType() == FOOD || __grid[i]->getType() == ADVANTAGE)
                r++;
        }
    }
    return r;
}

const Piece *Game::getPiece(unsigned int x, unsigned int y) const {

    if(__grid[((x*__width)+y)] != nullptr)
        return __grid[((x*__width)+y)];
    throw PositionEmptyEx(x,y);
}

void Game::addSimple(const Position &position) {
    Simple *s = new Simple(*this,position,STARTING_AGENT_ENERGY);

    if((position.x*__width + position.y)>__grid.size())
        throw OutOfBoundsEx(__width,__height,position.x,position.y);

    if((__grid[position.x*__width + position.y])!=nullptr)
        throw PositionNonemptyEx(position.x,position.y);

    __grid[position.x*__width + position.y] = s;
}

void Game::addSimple(const Position &position, double energy) {
    Simple *s = new Simple(*this,position,energy);

    if((position.x*__width + position.y)>__grid.size())
        throw OutOfBoundsEx(__width,__height,position.x,position.y);

    if((__grid[position.x*__width + position.y])!=nullptr)
        throw PositionNonemptyEx(position.x,position.y);

    __grid[position.x*__width + position.y] = s;
}

void Game::addSimple(unsigned x, unsigned y) {
    Position p(x,y);
    this->addSimple(p);
}

void Game::addSimple(unsigned x, unsigned y, double energy) {
    Position p(x,y);
    this->addSimple(p,energy);
}

void Game::addStrategic(const Position &position, Strategy *s) {
   Strategic *t = new Strategic(*this,position,STARTING_RESOURCE_CAPACITY,s);

    if((position.x*__width + position.y)>__grid.size())
        throw OutOfBoundsEx(__width,__height,position.x,position.y);

    if((__grid[position.x*__width + position.y])!=nullptr)
        throw PositionNonemptyEx(position.x,position.y);

    __grid[position.x*__width + position.y] = t;
}

void Game::addStrategic(unsigned x, unsigned y, Strategy *s) {
    Position p(x,y);
    this->addStrategic(p,s);
}

void Game::addFood(const Position &position) {
    Food *f = new Food(*this,position,STARTING_RESOURCE_CAPACITY);

    if((position.x*__width + position.y)>__grid.size())
        throw OutOfBoundsEx(__width,__height,position.x,position.y);

    if((__grid[position.x*__width + position.y])!=nullptr)
        throw PositionNonemptyEx(position.x,position.y);

    __grid[position.x*__width + position.y] = f;
}

void Game::addFood(unsigned x, unsigned y) {
    Position p(x,y);
    this->addFood(p);
}

void Game::addAdvantage(const Position &position) {
    Advantage *a = new Advantage(*this,position,STARTING_RESOURCE_CAPACITY);

    if((position.x*__width + position.y)>__grid.size())
        throw OutOfBoundsEx(__width,__height,position.x,position.y);

    if((__grid[position.x*__width + position.y])!=nullptr)
        throw PositionNonemptyEx(position.x,position.y);

    __grid[position.x*__width + position.y] = a;
}

void Game::addAdvantage(unsigned x, unsigned y) {
    Position p(x,y);
    this->addAdvantage(p);
}

const Surroundings Game::getSurroundings(const Position &pos) const {
    Surroundings temp;

    for (int i = 0; i < 3; ++i) {
        int tempX = pos.x-1;
        for (int j = 0; j < 3; ++j) {
            int tempY = pos.y-1;
            if(tempX < 0 ||tempX >__width || tempY<0 || tempY > __height) {
                temp.array[(i * 3) + j] = INACCESSIBLE;
            }
            else {
                temp.array[(i * 3) + j] = __grid[(tempX * __width) + tempY]->getType();
            }
            tempY++;
        }
        tempX++;

    }
    return temp;
}

const ActionType Game::reachSurroundings(const Position &from, const Position &to) {

    ActionType temp =STAY;
    int xDiff = to.x-from.x;
    int yDiff = to.y-from.y;

    if(xDiff == -1 && yDiff == -1)
        temp = NW;
    else if(xDiff == -1 && yDiff == 0)
        temp = N;
    else if(xDiff == -1 && yDiff == 1)
        temp =NE;
    else if(xDiff == 0 && yDiff == -1)
        temp =W;
    else if(xDiff == 0 && yDiff == 0)
        temp =STAY;
    else if(xDiff == 0 && yDiff == 1)
        temp =E;
    else if(xDiff == 1 && yDiff == -1)
        temp =SW;
    else if(xDiff == 1 && yDiff == 0)
        temp =S;
    else if(xDiff == 1 && yDiff == 1)
        temp =SE;


    return temp;
}

bool Game::isLegal(const ActionType &ac, const Position &pos) const {
//we don't have to compare to zero because x,y are unsigned
    return!(pos.x > __width || pos.y > __height);

}

const Position Game::move(const Position &pos, const ActionType &ac) const {
    if(ac == NW)
        return Position(pos.x-1,pos.y-1);
    else if(ac == N)
        return Position(pos.x-1,pos.y);
    else if(ac == NE)
        return Position(pos.x-1,pos.y+1);
    else if(ac == W)
        return Position(pos.x,pos.y-1);
    else if(ac == STAY)
        return Position(pos.x,pos.y);
    else if(ac == E)
        return Position(pos.x,pos.y+1);
    else if(ac == SW)
        return Position(pos.x+1,pos.y-1);
    else if(ac == S)
        return Position(pos.x+1,pos.y);
    else if(ac == SE)
        return Position(pos.x+1,pos.y+1);
    return pos;
}

void Game::round() {
    for (int i = 0; i < __grid.size(); ++i) {
        if(__grid[i]->isViable()){
            if(!__grid[i]->getTurned()){
                __grid[i]->setTurned(true);
                if(__grid[i]->getType() == SIMPLE || __grid[i]->getType() == STRATEGIC) {

                    ActionType aT = __grid[i]->takeTurn(getSurroundings(__grid[i]->getPosition()));
                    if(aT != STAY) {
                        Position movingPos = move(__grid[i]->getPosition(), aT);
                        if(__grid[((movingPos.x) * __width) + (movingPos.y)]!= nullptr) {
                            (*__grid[i]) * (*__grid[((movingPos.x) * __width) + (movingPos.y)]);
                            Agent *fromA = dynamic_cast<Agent *>(__grid[i]);
                            Agent *toA = dynamic_cast<Agent *>(__grid[((movingPos.x) * __width) + (movingPos.y)]);
                            if (fromA->isViable()) {
                                fromA->setPosition(toA->getPosition());
                                delete toA;
                                __grid[((movingPos.x) * __width) + (movingPos.y)] = fromA;
                                __grid[i] = nullptr;
                            }
                        } else {
                            __grid[i]->setPosition(__grid[((movingPos.x) * __width) + (movingPos.y)]->getPosition());
                            __grid[((movingPos.x) * __width) + (movingPos.y)] = __grid[i];
                            __grid[i]= nullptr;
                        }

                    }

                }
            }
        }
    }
}

void Game::play(bool verbose) {

}



std::ostream & Gaming::operator<<(std::ostream &os, const Game &game) {
    return os;
}





