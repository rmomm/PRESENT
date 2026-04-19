#pragma once
#include <string>
#include <vector>
#include <bitset>
#include <fstream>
#include <iostream>
#include <cstdint>

using namespace std;

vector<uint8_t> readFile(const string& filename);
void writeFile(const string& filename, const vector<uint8_t>& data);

