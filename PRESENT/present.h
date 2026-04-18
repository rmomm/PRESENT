#pragma once
#include <cstdint>
#include <array>
#include <vector>
#include <bitset>

using namespace std;

uint8_t sBox(uint8_t input);
uint8_t invsBox(uint8_t input);

uint64_t sBoxLayer(uint64_t state);
uint64_t invsBoxLayer(uint64_t state);

uint64_t pLayer(uint64_t state);
uint64_t invpLayer(uint64_t state);

uint64_t encrypt(uint64_t state, uint64_t addRoundKeys[32]);
uint64_t decrypt(uint64_t state, uint64_t addRoundKeys[32]);

vector<uint64_t> generateRoundKeys80(bitset<80> key);
vector<uint64_t> generateRoundKeys128(bitset<128> key);