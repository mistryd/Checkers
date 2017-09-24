#include "board.h"
#include "checkers.h"
#include "graphics.h"

#include <iostream>
using namespace std;


int main(int argc, char *argv[]) {
    int selection;
    cout << "1 for console, 2 for graphics: " << flush;
    cin >> selection;
    cout << flush;
    
    
    if (selection == 2) {
        graphicsPlay(argc, argv);
    }
    consolePlay();
    
    return 0;
}
