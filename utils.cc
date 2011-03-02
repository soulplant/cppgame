#include "utils.h"
#include <sstream>

using namespace std;

string showByte(Uint8 x) {
    // printf("showByte(%d)\n", x);
    stringstream result;
    for (int i = 0; i < 8; i++) {
        result << ((x & (1 << (8-i-1))) != 0);
    }
    return result.str();
}

string showInt(Uint32 x) {
    stringstream result;
    result << "[" << showByte((x & 0xff000000) >> 24) << "]";
    result << "[" << showByte((x & 0x00ff0000) >> 16) << "]";
    result << "[" << showByte((x & 0x0000ff00) >> 8) << "]";
    result << "[" << showByte((x & 0x000000ff)) << "]";
    return result.str();
}

