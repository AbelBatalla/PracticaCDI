#include "huffman.h"

using namespace std;
void Huffman::buildTree(const unordered_map<string, int>& frequencies) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    // Create a leaf node for each character and add it to the priority queue
    for (const auto& pair : frequencies) {
        pq.push(new Node(pair.first, pair.second));
    }

    // Build the Huffman tree
    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        Node* newNode = new Node("", left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        pq.push(newNode);
    }
    root = pq.top();
}

// Constructor
Huffman::Huffman(const string& str, const int len) {
    length = len;
    unordered_map<string, int> frequencies = calcularFreq(str, len);
    buildTree(frequencies);
    stack<bool> emptyCode;
    findCodes(root, emptyCode);
}

unordered_map<string, int> Huffman::calcularFreq(const string& str, const int len) {
    unordered_map<string, int> frequencies;
    for (int i = 0; i <= str.length() - len; i+=len) {
        string subStr = str.substr(i, len);
        frequencies[subStr]++;
    }
    return frequencies;
}

void Huffman::findCodes(Node* currentNode, stack<bool>& code) {

    if (currentNode->data.empty())
    {   //case base
        huffmanCodes[currentNode->data] = code;
    } 
    else{
        if (currentNode->left) {
            code.push(false);
            Huffman::findCodes(currentNode->left, code);
            code.pop();
        }
        if (currentNode->right) {
            code.push(true);
            Huffman::findCodes(currentNode->right, code);
            code.pop();
        }
    }
}

// Function to encode a given string
string Huffman::encode(string str) {
    string encoded;
    for (int i = 0; i<str.length(); i += length) {
        string subStr = str.substr(i, length);
        stack<bool> huffmanCode = huffmanCodes[subStr];
        while(!huffmanCode.empty()){ 
            encoded += huffmanCode.top() ? '1' : '0';
            huffmanCode.pop();
        }
    }
    return encoded;
}

// Function to decode a given encoded string
string Huffman::decode() {
    // TODO: Implement decoding logic here
    return "";
}
