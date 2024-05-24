#include "huffman.h"

map<string, vector<bool>> Huffman::invertMap(const map<vector<bool>, string>& inputMap){
    needsEncoded = false;
    map<string, vector<bool>> invertedMap;
    for (const auto& pair : inputMap)
    {
        invertedMap[pair.second] = pair.first;
    }
    return invertedMap;
}

string Huffman::toBinary(int n) {
    string r;
    while(n!=0) {
        r = (n % 2 == 0 ? "0" : "1") + r;
        n /= 2;
    }
    return r;
}

// Function to encode a given string
void Huffman::encode(ifstream& input, ofstream& output){
    if(needsEncoded)
        encoder = invertMap(decoder);

    string str;
    getline(input, str);
    char buffer = 0;
    int bitsWritten = 0;

    for ( int i = 0; i < str.size(); i += numberOfChars){
        string substr = str.substr(i, numberOfChars);
        auto it = encoder.find(substr);
        if (it == encoder.end()) {
            int l = numberOfChars;
            while(it == encoder.end())
            {
                --l;
                if(l <= 0)
                {
                    throw std::runtime_error("Substring not found: " + substr);
                }
                substr = str.substr(i, l);
                it = encoder.find(substr);
            }
            i -= numberOfChars-l;
        }
        vector<bool> bits = it->second;
        for (const auto& bit : bits) {
            buffer <<= 1;
            buffer += bit;
            bitsWritten++;
            if(bitsWritten == 8){
                output.write(&buffer, 1);
                bitsWritten = 0;
                buffer = 0;
            }
        }
    }
    buffer <<= 8-bitsWritten;
    output.write(&buffer, 1);
}

// Function to decode a given encoded string
void Huffman::decode(ifstream& input, ofstream& output) {
    char c;
    vector<bool> buffer;

    while(input.get(c)) {
        for (int i = 7; i >= 0; --i) {
            if ((c >> i) & 1) buffer.push_back(true);
            else buffer.push_back(false);
            auto it = decoder.find(buffer);
            if (it != decoder.end()) {
                buffer.clear();
                output.write(it->second.c_str(), it -> second.size());
            }
            else if (buffer.size() > 20) {
                throw std::runtime_error("Huffman code not found");
            }
        }
    }
}