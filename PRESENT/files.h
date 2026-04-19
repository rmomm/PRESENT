#pragma once
#include <string>
#include <vector>
#include <bitset>
#include <fstream>
#include <iostream>
#include <cstdint>
#include <stdexcept>

using namespace std;

struct KeyData {
    bool is128 = false;;
    bitset<80> key80;
    bitset<128> key128;
};

vector<uint8_t> readFile(const string& filename);
void writeFile(const string& filename, const vector<uint8_t>& data);

KeyData readKey(const string& filename);
vector<uint64_t> getRoundKeys(const KeyData& kd);

void encryptFile(const string& inputFile, const string& outputFile, const string& keyFile);
void decryptFile(const string& inputFile, const string& outputFile, const string& keyFile);
