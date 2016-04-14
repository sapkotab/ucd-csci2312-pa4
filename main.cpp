#include <iostream>
#include <fstream>
#include <sstream>


#include "ErrorContext.h"
#include "GamingTests.h"

using std::cout;
using std::endl;

using namespace Testing;

//#include "Game.h"
//#include "Simple.h"
//#include "Strategic.h"
//#include "Advantage.h"
//#include "Food.h"
//using namespace Gaming;

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
//    test_piece_turntaking(ec, NumIters);
//    test_piece_interaction(ec, NumIters);

    // surroundings tests
//    test_surroundings_smoketest(ec);

    // action tests
    test_action_smoketest(ec);

    // game tests
    test_game_smoketest(ec);
    test_game_populate(ec, NumIters);
    test_game_getpiece(ec, NumIters);
//    test_game_print(ec, NumIters);
//    test_game_randomization(ec, NumIters);
//    test_game_play(ec, NumIters);
//    Game g;                         // note: Game smoke test is needed first
//
//    Position p0(0, 0);
//    Simple s(g, p0, 10);
//
//    Position p1(1, 0);
//    Strategic t(g, p1, 20);
//
//    Position p2(2, 2);
//    Food f(g, p2, 5);
//
//    Position p3(0, 2);
//    Advantage a(g, p3, 3);
//
//    std::stringstream ss;
//    cout << s << ' ' << t << ' ' << f << ' ' << a;
    return 0;
}