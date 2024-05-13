#ifndef SHA256_Util
#define SHA256_Util
void printUint32Vector(const vector<uint32_t>& vec);
void printUint32VectorInBinary(const vector<uint32_t>& vec);
void printUint32InHex(uint32_t value);

void printUint32Vector(const vector<uint32_t>& vec) {
    cout << "Uint32_t:" <<endl;
    for (uint32_t val : vec) {
       cout << val <<endl;
    }
}

void printUint32VectorInBinary(const vector<uint32_t>& vec) {
    cout << "Uint32_t in binario:" << endl;
    for (uint32_t val : vec) {
        string binaryString = bitset<32>(val).to_string();
        for (size_t i = 0; i < binaryString.size(); i += 8) {
            cout << binaryString.substr(i, 8)<<" size: "<<binaryString.size();
            if (i + 8 < binaryString.size()) {
                cout << " "; // Aggiungi un tabulato ogni 8 bit
            }
        }
        cout << endl;
    }
}

void printUint32InHex(uint32_t value) {
    cout << hex << setw(8) << setfill('0') << value;
}

#endif
