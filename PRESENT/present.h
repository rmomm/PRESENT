#pragma once
#include <cstdint>

using namespace std;

uint8_t sBox(uint8_t v);
uint8_t invsBox(uint8_t v);

uint64_t sBoxLayer(uint64_t state);
uint64_t invsBoxLayer(uint64_t state);

uint64_t pLayer(uint64_t state);
uint64_t invpLayer(uint64_t state);