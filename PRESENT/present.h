#pragma once
#include <cstdint>
#include <array>
#include <vector>

using namespace std;

uint8_t sBox(uint8_t input);
uint8_t invsBox(uint8_t input);

uint64_t sBoxLayer(uint64_t state);
uint64_t invsBoxLayer(uint64_t state);

uint64_t pLayer(uint64_t state);
uint64_t invpLayer(uint64_t state);

uint64_t encrypt(uint64_t state, uint64_t addRoundKeys[32]);
uint64_t decrypt(uint64_t state, uint64_t addRoundKeys[32]);