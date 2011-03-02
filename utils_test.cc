#include <iostream>
#include "utils.h"

int main(int argc, char** argv) {
    short x = 256;
    // cout << showInt(3) << endl;
    cout << showByte(0xba) << endl;
    cout << showInt(0xbadcaffee) << endl;
    return 0;
}
