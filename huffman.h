#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
#include <stack>

using namespace std;

class Node {
    public:
        string data;
        int frequency;
        Node* left;
        Node* right;

        Node(string data, int frequency) {
            this->data = data;
            this->frequency = frequency;
            left = right = nullptr;
        }
};

struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->frequency > right->frequency;
    }
};

class Huffman
{
    private:
        Node* root;
        unordered_map<string, stack<bool>> huffmanCodes;
        int length;

        void buildTree(const unordered_map<string, int>& frequencies);

        void findCodes(Node* currentNode, stack<bool>& code);

        unordered_map<string, int> calcularFreq(const string& str, const int len);

    public:
        Huffman(const string& str, const int len);

        string encode(string str);

        string decode(string binary);
};

#endif