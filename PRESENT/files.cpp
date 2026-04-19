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


KeyData readKey(const string& filename) {
    ifstream in(filename);
    if (!in) { 
        throw runtime_error("Cannot open key file"); 
    }

    string hex;
    in >> hex;

    KeyData kd;

    if (hex.size() == 20) {
        kd.is128 = false;

        for (int i = 0; i < 20; i++) {
            uint8_t val = stoi(hex.substr(i, 1), nullptr, 16);
            for (int j = 0; j < 4; j++) {
                kd.key80[79 - (i * 4 + j)] = (val >> (3 - j)) & 1;
            }
        }
    }
    else if (hex.size() == 32) {
        kd.is128 = true;

        for (int i = 0; i < 32; i++) {
            uint8_t val = stoi(hex.substr(i, 1), nullptr, 16);
            for (int j = 0; j < 4; j++) {
                kd.key128[127 - (i * 4 + j)] = (val >> (3 - j)) & 1;
            }
        }
    }
    else {
        throw runtime_error("Key must be 80 or 128-bit hex");
    }

    return kd;
}

vector<uint64_t> getRoundKeys(const KeyData& kd) {
    if (kd.is128){ 
        return generateRoundKeys128(kd.key128); 
    } 
    else {
        return generateRoundKeys80(kd.key80);
    }
}


void encryptFile(const string& inputFile, const string& outputFile, const string& keyFile) {
    auto data = readFile(inputFile);
    auto kd = readKey(keyFile);

    auto keys = getRoundKeys(kd);

    uint64_t roundKeys[32];
    for (int i = 0; i < 32; i++) roundKeys[i] = keys[i];

    auto encrypted = encryptData(data, roundKeys);

    writeFile(outputFile, encrypted);

    cout << "Encryption done!\n";
}


void decryptFile(const string& inputFile, const string& outputFile, const string& keyFile) {
    auto data = readFile(inputFile);
    auto kd = readKey(keyFile);

    auto keys = getRoundKeys(kd);

    uint64_t roundKeys[32];
    for (int i = 0; i < 32; i++) roundKeys[i] = keys[i];

    auto decrypted = decryptData(data, roundKeys);

    writeFile(outputFile, decrypted);

    cout << "Decryption done!\n";
}