#include "huffman.h"

map<string, pair<short,short>> Huffman::invertMap(const map<pair<short,short>, string>& inputMap){
    needsEncoded = false;
    map<string, pair<short,short>> invertedMap;
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
string Huffman::encode(string str) {
    if(needsEncoded)
        encoder = invertMap(decoder);

    string encoded;
    for ( int i = 0; i < str.size(); i += 6){
        string substr = str.substr(i, 6);
        auto it = encoder.find(substr);
        if (it == encoder.end()) {
            int l = 6;
            while(it == encoder.end())
            {
                --l;
                substr = str.substr(i, l);
                it = encoder.find(substr);
            }
            i -= 6-l;
            if(l <= 0)
            {
                throw std::runtime_error("Substring not found: " + substr);
            }
        }
        pair<short, short> numpair = it->second;
        string bin = toBinary(numpair.second);
        if (bin.length() < numpair.first) {
            bin = string(numpair.first - bin.length(), '0') + bin;
        }
        encoded += bin;
    }
    return encoded;
}

// Function to decode a given encoded string
string Huffman::decode(string binary) {
    string decoded;
    for (int i = 0; i < binary.size(); ++i) {
        for (int len = 1; i + len <= binary.size(); ++len) {
            string substr = binary.substr(i, len);
            auto it = decoder.find({substr.size(), stoi(substr, nullptr, 2)});
            if (it != decoder.end()) {
                decoded += it->second;
                i += len-1;
                break;
            }
            else if (substr.size() > 20) {
                throw std::runtime_error("Substring not found: " + substr);
            }
        }
    }
    
    return decoded;
}
