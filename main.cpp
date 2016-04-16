#include <iostream>
#include <fstream>
#include <sstream>


#include "ErrorContext.h"
#include "GamingTests.h"

using std::cout;
using std::endl;

using namespace Testing;

#include "Game.h"
#include "Simple.h"
#include "Strategic.h"
#include "Advantage.h"
#include "Food.h"
//#include "AggressiveAgentStrategy.h" //TODO edited
using namespace Gaming;

int main() {

    const int NumIters = 3;

    cout << endl << "Testing PA4!!" << endl << endl;

    cout << "NOTE:  If you see any memory errors, you MUST fix them!" << endl;
    cout << "       Tests intentionally invoke destructors after they complete,"
    << endl;
    cout << "       so if you see a seg-fault after a passed test, it is"
    << endl;
    cout << "       probably a bug in your destructor." << endl;

    cout << endl;

    ErrorContext ec(cout);

    // piece tests
    test_piece_smoketest(ec);
    test_piece_print(ec, NumIters);
    test_piece_aging(ec, NumIters);
    test_piece_energy(ec, NumIters);
    test_piece_turntaking(ec, NumIters);
    test_piece_interaction(ec, NumIters);

    // surroundings tests
    test_surroundings_smoketest(ec);

    // action tests
    test_action_smoketest(ec);

    // game tests
    test_game_smoketest(ec);
    test_game_populate(ec, NumIters);
    test_game_getpiece(ec, NumIters);
    test_game_print(ec, NumIters);
    test_game_randomization(ec, NumIters);
    test_game_play(ec, NumIters);

//    Game g; // manual = true, by default
//    // In this configuration, the Simple and Strategic are far from each other
//    // and they might or might not get close to each other before the
//    // Resources run out
//    g.addStrategic(0, 1, new AggressiveAgentStrategy(Game::STARTING_AGENT_ENERGY));
//    g.addSimple(2, 1);
//    g.addFood(0, 2);
//    g.addFood(2, 2);
//    g.addAdvantage(1, 0);
//    Piece *T = (Piece *) g.getPiece(0, 1);
//    Piece *S = (Piece *) g.getPiece(1, 1);
//    Piece *F1 = (Piece *) g.getPiece(0, 2);
//    Piece *F2 = (Piece *) g.getPiece(2, 2);
//    Piece *D = (Piece *) g.getPiece(, 1);
//
//
//
//    g.play(); // verbose = false, by default
    return 0;
}