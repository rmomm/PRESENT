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

