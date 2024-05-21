#include "huffman.h"
#include <fstream>
#include <cstdint>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <-c|-d> <filename>" << std::endl;
        return 1;
    }
    std::string mode = argv[1];
    std::string filename = argv[2];

    if (mode == "-c") {
    Huffman h;
    string dna;
    ifstream inputFile(filename); // Open the DNA sequence file

    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file." << endl;
        return 1; // Exit if file is not opened successfully
    }

    getline(inputFile, dna); // Read the DNA sequence from the file
    inputFile.close(); // Close the file after reading

    auto compressedBytes = h.encode(dna);
    cout << "Compressed" << endl;

    // Open a file in binary mode to write the compressed data
    ofstream outputFile(filename+".cda", ios::out | ios::binary);
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open the file for writing." << endl;
        return 1;
    }

    // Write the compressed data to the file
    outputFile.write(reinterpret_cast<const char*>(compressedBytes.data()), compressedBytes.size());
    outputFile.close(); // Close the file after writing
    cout << "Written" << endl;

    return 0;
    }
    else if(mode == "-d")
    {}
    else{
        std::cerr << "Usage: " << argv[0] << " <-c|-d> <filename>" << std::endl;
        return 1;
    }

}