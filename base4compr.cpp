#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <limits>

using namespace std;
vector<string> _simbols = {"A","G","C","T"};
void compressArithm(ifstream& input, vector<string> simbols,ofstream& output)
{
    string in;
    char c;
    unsigned long out = 0;
    int stringLength = simbols[0].size();
    while (input.get(c))
    {
        in = c;
        while(in.size() < stringLength)
        {
            input.get(c);
            in += c;
        }
        if(out >= numeric_limits<unsigned long>::max()/4)
        {
            unsigned long value = out;
            output.write(reinterpret_cast<const char*>(&value), sizeof(value));
            out = 0;
            //cout << "Written: " << value;
        }
        unsigned long _in;
        if (in == "A") _in = 0;
        else if (in == "G") _in = 1;
        else if (in == "C") _in = 2;
        else if (in == "T") _in = 3;
        out = out * 4 + _in;
    }
    unsigned long value = out;
    //cout << "Written last: " << value << "\n";
    output.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

string _decompressArithm(unsigned long in, vector<string>& simbols)
{
    string out = "";
    while (in != 0)
    {
        out = simbols[in % 4] + out;
        in = in / 4;
    }
    return out;
}

void decompressArithm(ifstream& in, vector<string>& simbols, ofstream& out)
{
    unsigned long value;
    string output = "";
    while (in.read(reinterpret_cast<char*>(&value), sizeof(value)))
    {
        //cout << "Read: " << value;
        output = output + _decompressArithm(value, simbols);
    }
    out << output;
}
 

    int main()
    {
        // Open the file
        ifstream inputFile("C:/Users/david/Documents/GitHub/PracticaCDI/DNACorpus/AgPh");
        
        // Check if the file was opened successfully
        if (!inputFile)
        {
            cout << "Failed to open the input file." << endl;
            return 1;
        }

        ofstream outputFile("output.bin", std::ios::binary);

        // Check if the file was opened successfully
        if (!outputFile)
        {
            std::cout << "Failed to open the output file." << std::endl;
            return 1;
        }
        
        compressArithm(inputFile, _simbols, outputFile);

        // Close the file
        inputFile.close();
        outputFile.close();

        // Open the file
        ifstream inputFile2("output.bin", std::ios::binary);

        // Check if the file was opened successfully
        if (!inputFile2)
        {
            cout << "Failed to open the input file." << endl;
            return 1;
        }

        ofstream outputFile2("output.txt");

        // Check if the file was opened successfully
        if (!outputFile2)
        {
            std::cout << "Failed to open the output file." << std::endl;
            return 1;
        }

        decompressArithm(inputFile2, _simbols, outputFile2);

        // Close the file
        inputFile2.close();
        outputFile2.close();

        
        return 0;
    }