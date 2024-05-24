#include "huffman.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <-c|-d> <filename>" << std::endl;
        return 1;
    }
    std::string mode = argv[1];
    std::string filename = argv[2];

    if (mode == "-c") {
        Huffman h;
        ifstream inputFile(filename); // Open the DNA sequence file

        if (!inputFile.is_open()) {
            std::cerr << "Failed to open the file." << endl;
            return 1; // Exit if file is not opened successfully
        }

        ofstream outputFile(filename+".cda", ios::out | ios::binary);
        if (!outputFile.is_open()) {
            std::cerr << "Failed to open the file for writing." << endl;
            return 1;
        }
        

        h.encode(inputFile, outputFile);
        cout << "Compressed" << endl;

        inputFile.close(); // Close the file after reading
        outputFile.close(); // Close the file after writing
        return 0;
    }
    else if(mode == "-d")
    {
        if (filename.size() < 4 or filename.substr(filename.size() - 4, 4) != ".cda") {
                std::cerr << "Wrong format for decoding, must be a .cda" << endl;
                return 1; // Exit if file is correct format
        }

        Huffman h;
        ifstream inputFile(filename, ios::binary); // Open the DNA sequence compressed file
        if (!inputFile.is_open()) {
            std::cerr << "Failed to open the file." << endl;
            return 1; // Exit if file is not opened successfully
        }

        ofstream outputFile(filename.substr(0, filename.size() - 4)+".dcp", ios::out | ios::binary);
        if (!outputFile.is_open()) {
            std::cerr << "Failed to open the file for writing." << endl;
            return 1;
        }
        

        h.decode(inputFile, outputFile);
        cout << "Decompressed" << endl;

        inputFile.close(); // Close the file after reading
        outputFile.close(); // Close the file after writing

        return 0;
    }
    else{
        std::cerr << "Usage: " << argv[0] << " <-c|-d> <filename>" << std::endl;
        return 1;
    }
}