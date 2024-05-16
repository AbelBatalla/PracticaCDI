#include "huffman.h"
#include <fstream>
#include <cstdint>

main()
{
    /*
    string test = "GCCGCCCCCATGGTCCATACGGTGTGCGAATACGGCGTGGCCCTCCTTACCCCATCCAGGCCTCTCTACGCCCCACTTGTCTATAGTGCCTTTCACGACCCTGGCCACAAGGTCGATCGCGTACTCCCAGGAGACAGGCTCTAGCCTTCCTCAA";
    
    cout << "Encoding: " << test << endl;
    string decoding = h.encode(test);
    cout << decoding << endl;//*/
    Huffman h;
    string dna;
    ifstream inputFile("./AgPh"); // Open the DNA sequence file

    if (!inputFile.is_open()) {
        cout << "Failed to open the file." << endl;
        return 1; // Exit if file is not opened successfully
    }

    getline(inputFile, dna); // Read the DNA sequence from the file
    inputFile.close(); // Close the file after reading

    auto compressedBytes = h.encode(dna);
    cout << "Compressed" << endl;
    

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




    /*
    cout << "\nDecoding: " << endl;
    cout << h.decode(decoding) << endl;
    cout << "Original: " << endl;
    cout << test << endl;//*/
    


}