#include <iostream>
#include "present.h"

int main() {
    uint64_t test = 0x0123456789ABCDEF;

    uint64_t enc = sBoxLayer(test);
    uint64_t dec = invsBoxLayer(enc);

    cout << hex << test << endl;
    cout << enc << endl;
    cout << dec << endl;

    cout << endl;

    uint64_t perm = pLayer(test);
    uint64_t inv = invpLayer(perm);

    cout << hex << test << endl;
    cout << perm << endl;
    cout << inv << endl;

    return 0;
}