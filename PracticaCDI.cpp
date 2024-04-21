#include <iostream>
#include <vector>
#include <cstdint>
#include <fstream>
using namespace std;

// Function to compress DNA sequence into a vector of bytes
vector<uint8_t> compressDNA(const string& dna) {
    vector<uint8_t> compressed;
    int bitPos = 0;
    uint8_t currentByte = 0;

    for (char nucleotide : dna) {
        uint8_t bits;
        switch (nucleotide) {
            case 'A': bits = 0b00; break;
            case 'C': bits = 0b01; break;
            case 'T': bits = 0b10; break;
            case 'G': bits = 0b11; break;
            default:  continue;  // In case of invalid character
        }

        // Shift the bits into the correct position
        currentByte |= (bits << (6 - bitPos));
        bitPos += 2;

        // If the current byte is full, add it to the vector
        if (bitPos == 8) {
            compressed.push_back(currentByte);
            currentByte = 0;  // Reset for the next byte
            bitPos = 0;
        }
    }

    // Add the last byte if it contains any bits
    if (bitPos != 0) {
        compressed.push_back(currentByte);
    }

    return compressed;
}

// Function to print bytes in binary form for verification
void printCompressed(const vector<uint8_t>& compressed) {
    for (uint8_t byte : compressed) {
        for (int i = 7; i >= 0; --i) {
            cout << ((byte >> i) & 1);
        }
        cout << " ";
    }
    cout << endl;
}

int main() {
    string dna;
    ifstream inputFile("./dna_sequence.txt"); // Open the DNA sequence file

    if (!inputFile.is_open()) {
        cout << "Failed to open the file." << endl;
        return 1; // Exit if file is not opened successfully
    }

    getline(inputFile, dna); // Read the DNA sequence from the file
    inputFile.close(); // Close the file after reading

    auto compressedBytes = compressDNA(dna);
    cout << "Compressed" << endl;
    //cout << dna << " Compressed DNA sequence as binary: ";
    //printCompressed(compressedBytes);

    // Open a file in binary mode to write the compressed data
    ofstream outputFile("compressed_dna.cda", ios::out | ios::binary);
    if (!outputFile.is_open()) {
        cout << "Failed to open the file for writing." << endl;
        return 1;
    }

    // Write the compressed data to the file
    outputFile.write(reinterpret_cast<const char*>(compressedBytes.data()), compressedBytes.size());
    outputFile.close(); // Close the file after writing
    cout << "Written" << endl;
    
    return 0;
}
