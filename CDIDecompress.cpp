#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

using namespace std;

// Function to decompress DNA from a vector of bytes
string decompressDNA(const vector<uint8_t>& compressed) {
    string dna;
    for (uint8_t byte : compressed) {
        for (int i = 6; i >= 0; i -= 2) {  // Process each byte from the most significant pair to least
            uint8_t bits = (byte >> i) & 0b11;
            switch (bits) {
                case 0b00: dna += 'A'; break;
                case 0b01: dna += 'C'; break;
                case 0b10: dna += 'T'; break;
                case 0b11: dna += 'G'; break;
            }
        }
    }
    return dna;
}

// Function to read compressed binary data from a file
vector<uint8_t> readCompressedData(const string& filename) {
    ifstream inputFile(filename, ios::binary | ios::ate);
    if (!inputFile.is_open()) {
        cerr << "Failed to open the file." << endl;
        return {};  // Return an empty vector on failure
    }

    // Get the size of the file and allocate a buffer
    streamsize size = inputFile.tellg();
    inputFile.seekg(0, ios::beg);

    vector<uint8_t> buffer(size);
    if (!inputFile.read(reinterpret_cast<char*>(buffer.data()), size)) {
        cerr << "Failed to read the file." << endl;
        return {};  // Return an empty vector on failure
    }

    inputFile.close();
    return buffer;
}

int main() {
    const string filename = "compressed_dna.cda";
    const string outputFilename = "ORIGINAL_dna";

    vector<uint8_t> compressedData = readCompressedData(filename);

    if (compressedData.empty()) {
        cerr << "No data to decompress or failed to read the file." << endl;
        return 1;
    }

    string dna = decompressDNA(compressedData);

    // Open a file to write the decompressed DNA sequence
    ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        cerr << "Failed to open the file for writing." << endl;
        return 1;
    }

    outputFile << dna;  // Write the decompressed DNA sequence to the file
    outputFile.close();  // Close the file after writing

    cout << "Decompressed DNA sequence written to " << outputFilename << endl;
    //cout << "Decompressed DNA sequence: " << dna << endl;

    return 0;
}
