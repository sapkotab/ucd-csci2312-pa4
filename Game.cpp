//
// Created by bhuwan sapkota on 4/2/16.
//
#include <iomanip>
#include "Game.h"
#include "Simple.h"
#include "Strategic.h"
#include "Advantage.h"
#include "Food.h"


using namespace Gaming;

// even this is declared on class it is not initialized because
// it is declared as static so has to declare her so it will be initialized
PositionRandomizer Game::__posRandomizer;

// given constants requirements assignment
const unsigned  int Game::NUM_INIT_AGENT_FACTOR = 4;
const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;
const unsigned int Game::MIN_WIDTH = 3;
const unsigned int Game::MIN_HEIGHT = 3;
const double Game::STARTING_AGENT_ENERGY = 20;
const double Game::STARTING_RESOURCE_CAPACITY = 10;

// automatic populator of grid will be called on regular constructor, if  mannual is off.
void Game::populate() {

    // constants requiremnts according to assignment.
    __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
    __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
    unsigned int numStrategic = __numInitAgents / 2;
    unsigned int numSimple = __numInitAgents - numStrategic;
    unsigned int numAdvantages = __numInitResources / 4;
    unsigned int numFoods = __numInitResources - numAdvantages;

    // simple pseudo-random number generator
    std::default_random_engine gen;
    std::uniform_int_distribution<int> d(0, __width * __height-1); // d is the range


    // populate Strategic agents
    while (numStrategic > 0) {
        int i = d(gen); // random index in the grid vector
        if (__grid[i] == nullptr) { // is position empty
            Position pos(i / __width, i % __width);
            __grid[i] = new Strategic(*this, pos, STARTING_AGENT_ENERGY);
            numStrategic --;
        }
    }
    // populate Simple agents
    while (numSimple > 0) {
        int i = d(gen); // random index in the grid vector
        if (__grid[i] == nullptr) { // is position empty
            Position pos(i / __width, i % __width);
            __grid[i] = new Simple(*this, pos, STARTING_AGENT_ENERGY);
            numSimple --;
        }
    }
    // populate advantages
    while (numAdvantages > 0) {
        int i = d(gen); // random index in the grid vector
        if (__grid[i] == nullptr) { // is position empty
            Position pos(i / __width, i % __width);
            __grid[i] = new Advantage(*this, pos, STARTING_RESOURCE_CAPACITY);
            numAdvantages --;
        }
    }
    // populate Foods
    while (numFoods > 0) {
        int i = d(gen); // random index in the grid vector
        if (__grid[i] == nullptr) { // is position empty
            Position pos(i / __width, i % __width);
            __grid[i] = new Food(*this, pos, STARTING_RESOURCE_CAPACITY);
            numFoods --;
        }
    }

}

// constructor
// grid need to be filled with nullptr
Game::Game() {
    __numInitAgents = 0;
    __numInitResources = 0;
    __width = 3;
    __height = 3;
    __round = 0;
    __status = NOT_STARTED ;
    __verbose = false;  // this is used to print the game if true it will print the game round by when
                        // calling the play(). e.g g.play(true)
    for (int i = 0; i < __width*__height; ++i) {
        __grid.push_back(nullptr) ;
    }

}

Game::Game(unsigned width, unsigned height, bool manual) {
    // exception if width and height are less than 3
    if(width < MIN_WIDTH || height < MIN_HEIGHT)
        throw InsufficientDimensionsEx(MIN_WIDTH,MIN_HEIGHT,width,height);

    // regular initialization of variables.
    __numInitAgents = 0;
    __numInitResources = 0;
    __width = width;
    __height = height;
    __verbose = false;
    __status = NOT_STARTED;
    __round = 0;
    for (int i = 0; i < __width*__height; ++i) {
        __grid.push_back(nullptr) ;
    }
    //if not manual call this so grid will be filled.
    if(!manual)
        populate();
}

Game::~Game() { // deleting all the grids if they are filled.

    // deallocate the grid
    for (int i = 0; i < __grid.size(); ++i) {
       if (__grid[i] != nullptr)
           delete __grid[i];
    }
}

//getters
unsigned int Game::getNumPieces() const {
    return getNumAgents()+getNumResources();
}

unsigned int Game::getNumAgents() const {
    return getNumSimple()+getNumStrategic();
}

// going through the grid and counting
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
// going through the grid and counting
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
// going through the grid and counting
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

//find the vector index of grid based on position.
// return only it is not empty otherwise through exception.
const Piece *Game::getPiece(unsigned int x, unsigned int y) const {

    if(__grid[((x*__width)+y)] != nullptr)
        return __grid[((x*__width)+y)];
    throw PositionEmptyEx(x,y);
}

// creating the simple on heap and trafering to the the grid location
// throw exception if the position is outof bound or position is already filled
void Game::addSimple(const Position &position) {
    Simple *s = new Simple(*this,position,STARTING_AGENT_ENERGY);

    if((position.x*__width + position.y)>__grid.size())
        throw OutOfBoundsEx(__width,__height,position.x,position.y);

    if((__grid[position.x*__width + position.y])!=nullptr)
        throw PositionNonemptyEx(position.x,position.y);

    __grid[position.x*__width + position.y] = s;
}

// creating the simple on heap and trasfering to the the grid location
// throw exception if the position is out of bound or position is already filled
void Game::addSimple(const Position &position, double energy) {
    Simple *s = new Simple(*this,position,energy);

    if((position.x*__width + position.y)>__grid.size())
        throw OutOfBoundsEx(__width,__height,position.x,position.y);

    if((__grid[position.x*__width + position.y])!=nullptr)
        throw PositionNonemptyEx(position.x,position.y);

    __grid[position.x*__width + position.y] = s;
}

//passing coordinate instead of position
// similar to above.
void Game::addSimple(unsigned x, unsigned y) {
    Position p(x,y);
    this->addSimple(p);
}
//passing coordinate instead of position
// similar to above.
void Game::addSimple(unsigned x, unsigned y, double energy) {
    Position p(x,y);
    this->addSimple(p,energy);
}

// creating the strategic on heap and trasfering to the the grid location
// throw exception if the position is out of bound or position is already filled
void Game::addStrategic(const Position &position, Strategy *s) {
   Strategic *t = new Strategic(*this,position,STARTING_AGENT_ENERGY,s);

    if((position.x*__width + position.y)>__grid.size())
        throw OutOfBoundsEx(__width,__height,position.x,position.y);

    if((__grid[position.x*__width + position.y])!=nullptr)
        throw PositionNonemptyEx(position.x,position.y);

    __grid[position.x*__width + position.y] = t;
}

// co-ordinate instead of position
void Game::addStrategic(unsigned x, unsigned y, Strategy *s) {
    Position p(x,y);
    this->addStrategic(p,s);
}
// creating the food on heap and trasfering to the the grid location
// throw exception if the position is out of bound or position is already filled
void Game::addFood(const Position &position) {
    Food *f = new Food(*this,position,STARTING_RESOURCE_CAPACITY);

    if((position.x*__width + position.y)>__grid.size())
        throw OutOfBoundsEx(__width,__height,position.x,position.y);

    if((__grid[position.x*__width + position.y])!=nullptr)
        throw PositionNonemptyEx(position.x,position.y);

    __grid[position.x*__width + position.y] = f;
}
// co-ordinate instead of position
void Game::addFood(unsigned x, unsigned y) {
    Position p(x,y);
    this->addFood(p);
}
// creating the advantage on heap and trasfering to the the grid location
// throw exception if the position is out of bound or position is already filled
void Game::addAdvantage(const Position &position) {
    Advantage *a = new Advantage(*this,position,STARTING_RESOURCE_CAPACITY);

    if((position.x*__width + position.y)>__grid.size())
        throw OutOfBoundsEx(__width,__height,position.x,position.y);

    if((__grid[position.x*__width + position.y])!=nullptr)
        throw PositionNonemptyEx(position.x,position.y);

    __grid[position.x*__width + position.y] = a;
}
// co-ordinate instead of position
void Game::addAdvantage(unsigned x, unsigned y) {
    Position p(x,y);
    this->addAdvantage(p);
}

// creates the surring array based on passed postion
// which will be filled with enum "piecetype"
const Surroundings Game::getSurroundings(const Position &pos) const {

    Surroundings temp;          // creating temp surrounding
    int tempX = pos.x-1;        //starting from NW where x co-ordinate is one less than position's x

    for (int i = 0; i < 3; ++i) {
        int tempY = pos.y-1;        // starting from NW where y co-ordinate is one less than position's y
        for (int j = 0; j < 3; ++j) {
            if(((tempX * __width) + tempY)==((pos.x*__width)+pos.y))    // if temp position match with itself fill with self
                temp.array[(i * 3) + j] = SELF;
                // some position may be out of grid if so fill with inaccessible
                // e.g for position (0,1) N,NW,NE are inaccessible
            else if(tempX < 0 ||tempX >__height-1 || tempY<0 || tempY > __width-1) {
                temp.array[(i * 3) + j] = INACCESSIBLE;
            }
                // if the temp position is empty
            else if (__grid[(tempX * __width) + tempY] == nullptr)
                temp.array[(i * 3) + j] = EMPTY;
                // rest fill with whatever is in there by calling type.
            else {
                temp.array[(i * 3) + j] = __grid[(tempX * __width) + tempY]->getType();
            }
            tempY++; // increse temp y
        }
        tempX++;    // increse temp x

    }
    return temp; // temp is the struct that has array of surring of given position
}

const ActionType Game::reachSurroundings(const Position &from, const Position &to) {

    // return the enum direction or stay based on where to where
    // comparing their co-ordinate is the main concept here.
    // could have used switch statement but it is the same complexity.
    ActionType temp;
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
    else if(xDiff == 0 && yDiff == 1)
        temp =E;
    else if(xDiff == 1 && yDiff == -1)
        temp =SW;
    else if(xDiff == 1 && yDiff == 0)
        temp =S;
    else if(xDiff == 1 && yDiff == 1)
        temp =SE;
    else
        temp =STAY;

    return temp;
}

bool Game::isLegal(const ActionType &ac, const Position &pos) const {

    // creating surrounding based on pos and checking the position is
    // accessible. if accessible return true otherwise false.
    Surroundings ss = getSurroundings(pos);
    std::vector <ActionType> direction = {NW,N,NE,W,STAY,E,SW,S,SE};
    int directionInt;
    bool valid;
    for (int i = 0; i < direction.size(); ++i) {
        if(direction[i]== ac) {
            directionInt = i;
            break;
        }
    }
    valid = ss.array[directionInt] != INACCESSIBLE;

    return valid;

}

const Position Game::move(const Position &pos, const ActionType &ac) const {

    Position newPos;
    // finding the position of new grid on that direction.
    // and returning the direction.
    if(ac == NW)
        newPos = Position(pos.x-1,pos.y-1);
    else if(ac == N)
        newPos = Position(pos.x-1,pos.y);
    else if(ac == NE)
        newPos = Position(pos.x-1,pos.y+1);
    else if(ac == W)
        newPos = Position(pos.x,pos.y-1);
    else if(ac == STAY)
        newPos = Position(pos.x,pos.y);
    else if(ac == E)
        newPos = Position(pos.x,pos.y+1);
    else if(ac == SW)
        newPos = Position(pos.x+1,pos.y-1);
    else if(ac == S)
        newPos = Position(pos.x+1,pos.y);
    else if(ac == SE)
        newPos = Position(pos.x+1,pos.y+1);

    return newPos;
}

void Game::round() {
    // print initial grid
    if(__round == 0 && __verbose){
        __status = PLAYING;
        std::cout << std::endl << *this;
    }
    for (int i = 0; i < __grid.size(); ++i) {               // to iterate through grid vector.
        if(__grid[i]!= nullptr){                            // if grid is not empty
            if(__grid[i]->isViable()) {                     // piece is viable
                if (!__grid[i]->getTurned()) {
                    Agent * agent = dynamic_cast<Agent*>(__grid[i]);    // casting the piece to agent
                    if(agent) {                                     // if piece is agent, if resource if statement will be invalid
                        __grid[i]->setTurned(true);                     // tag as a participant on that round. only once per round
                        Position currentPos = __grid[i]->getPosition(); // current position
                        Surroundings s = getSurroundings(currentPos);   // creating surrounding
                        ActionType aT = __grid[i]->takeTurn(s);         // finding the direction to go
                        if (aT != STAY) {                               // if it want to move to another grid
                            Position newPos = move(currentPos, aT);     // finding the position of new location
                            int newPosIndx = (newPos.x * __width + newPos.y); // new grid index
                            (*__grid[i]) * (*__grid[newPosIndx]);           // interaction between pieces
                            if(!__grid[i]->isViable()){                     // if it is dead take care.
                                delete __grid[i];
                                __grid[i]= nullptr;
                            }
                            else {                                      // if it is not dead move to new location
                                __grid[i]->setPosition(newPos);
                                if (__grid[newPosIndx] != nullptr) {       // if new position is not empty take care that
                                    delete __grid[newPosIndx];
                                    __grid[newPosIndx] = __grid[i];
                                    __grid[i] = nullptr;
                                }
                                else {
                                    __grid[newPosIndx] = __grid[i];
                                    __grid[i] = nullptr;        // old position
                                }
                            }
                            if(!__grid[newPosIndx]->isViable()){ // this will take effect if both died after interacton.
                                delete __grid[newPosIndx];
                                __grid[newPosIndx]= nullptr;
                            }
                        }
                    }
                }
            }
        }
    }

    // delete each unviable piece and
    // take the participant tag off of each viable

    for (int j = 0; j < __grid.size(); ++j) {
        if(__grid[j] != nullptr) {
            if (!__grid[j]->isViable()) {
                delete __grid[j];
                __grid[j] = nullptr;
            }
            else {
                __grid[j]->setTurned(false);
                __grid[j]->age();
            }
        }
    }

    // changing status
    if(getNumPieces()< 2 || getNumResources() < 1)
        __status = OVER;
    //incrementing round
    ++__round;

    //print the grid if verbose is true.

    if(__verbose)
        std::cout << std::endl << *this;

}

void Game::play(bool verbose) {

    __verbose = verbose; // only used weather to print the grid each round
    round();
    // if condition is not met to finish the game keep going.
    if(getNumPieces()>1 && getNumResources() > 0) {
        play(verbose);
    }
}


// overloaded extraction operator that will print the grid of the game.

std::ostream & Gaming::operator<<(std::ostream &os, const Game &game) {
    os << "Round " << game.__round << std::endl;
    for (int i = 0; i < game.__height; ++i) {
        for (int j = 0; j < game.__width; ++j) {
            os << '[' << std::setw(5) <<std::left << *game.__grid[i*game.__width+j] << ']';
        }
        os << std::endl;
    }
// following is the status printing
    if(game.__status == Game::NOT_STARTED)
        os << "Status: Not Started...";
    else if(game.__status == Game::PLAYING)
        os << "Status: Playing...";
    else
        os << "Status: Over!";

    return os;
}





