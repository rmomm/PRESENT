#include "present.h"
#include "files.h"

vector<uint8_t> readFile(const string& filename) {
    ifstream in(filename, ios::binary);
    if (!in) {
        throw runtime_error("Cannot open input file");
    }

    in.seekg(0, ios::end);
    size_t size = in.tellg();
    in.seekg(0, ios::beg);

    vector<uint8_t> data(size);
    in.read(reinterpret_cast<char*>(data.data()), size);

    return data;
}

void writeFile(const string& filename, const vector<uint8_t>& data) {
    ofstream out(filename, ios::binary);
    if (!out) { 
        throw runtime_error("Cannot open output file");
    }

    out.write(reinterpret_cast<const char*>(data.data()), data.size());
}

bitset<80> readKey80(const string& filename) {
    ifstream in(filename);
    if (!in) {
        throw runtime_error("Cannot open key file");
    }

    string hex;
    in >> hex;

    if (hex.size() != 20) {
        throw runtime_error("Key must be 80-bit");
    }

    bitset<80> key;

    for (int i = 0; i < 20; i++) {
        uint8_t val = std::stoi(hex.substr(i, 1), nullptr, 16);
        for (int j = 0; j < 4; j++) {
            key[79 - (i * 4 + j)] = (val >> (3 - j)) & 1;
        }
    }

    return key;
}
