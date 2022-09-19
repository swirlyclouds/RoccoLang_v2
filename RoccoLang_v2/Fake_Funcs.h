#pragma once
#ifndef FAKE_FUNCS
#define FAKE_FUNCS
#endif // !FAKE_FUNCS

#include <iostream>
#include <random>
#include <string.h>
/*
This file provides the same format of functions used in the mbed program.
It exists for testing
*/

enum PinName { p17, p18, p19, p20 };
class Sharp {
public:
    Sharp(PinName inp) {

    }
    float getIRDistance() {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(15, 80); // distribution in range [1, 6]
        return dist6(rng);
    }
};

class HCSR04 {
public:
    HCSR04(PinName echo, PinName trig) {

    }
    long distance(int sys) {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 400); // distribution in range [1, 6]
        return dist6(rng);
    }
};

void wait(float x) {
    return;
}

class m3pi {
public:
    void locate(int a, int b) {}
    int printf(std::string n) {
        std::cout << "ROBOT OUTPUT: " << n << std::endl;
        return 1;
    }
    void cls() {}
};