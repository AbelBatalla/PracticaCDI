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

void printVectorBool(const std::vector<bool>& vec) {
    for (bool b : vec) {
        std::cout << b; // bool is automatically converted to 0 or 1 when printed
    }
    std::cout << std::endl; // Add a newline at the end for readability
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
        if (count >= 0) {
            cout << "Encoding: " << it->first << endl;
            printVectorBool(bits);
            --count;
            }
        for (const auto& bit : bits) {
            buffer <<= 1;
            buffer += bit;
            bitsWritten++;
            if(bitsWritten == 8){
                if (count >= 0) cout << "Writing: " << buffer << endl;
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
    //read(char* buffer, std::streamsize count)

    //vector<char> data((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());

    /*
        // Determine the size of the file
    input.seekg(0, std::ios::end);
    std::streamsize size = input.tellg();
    input.seekg(0, std::ios::beg);

    // Prepare a buffer to hold the data
    std::vector<char> datas(size);

    // Read the data
    input.read(datas.data(), size);

    cout << "Size: " << size << endl;
    cout << "Count: " << input.gcount() << endl;

    if (input.eof()) {
        std::cout << "End of file reached." << std::endl;
    }
    // Check if all data was read successfully
    if (input.gcount() != size) {
        throw std::runtime_error("Error reading file");
    }

    for (char c : datas) {
        */
    while(input.get(c)) {
        //cout << "\nDecoding char: " << c << endl;
        for (int i = 7; i >= 0; --i) {
            if ((c >> i) & 1) {
                buffer.push_back(true);
                //cout << 1;
                }
            else {
                buffer.push_back(false);
                //cout << 0;
            }
            auto it = decoder.find(buffer);
            if (it != decoder.end()) {
                //cout << "\nFound code: ";
                //printVectorBool(buffer);
                buffer.clear();
                //cout << it->second << endl;
                output.write(it->second.c_str(), it -> second.size());
            }
            else if (buffer.size() > 30) {
                throw std::runtime_error("Huffman code not found");
            }
        }
    }
    cout << "Finished" << endl;
}