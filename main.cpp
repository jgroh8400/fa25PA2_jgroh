//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);
    cout << "root " << root << endl;

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// BuildEncodingTree - creates a minheap, pushes all indices of weightArr into it, and then runs through while loop
// to find left and child pointers, root node value, and parent weight. returns root.
int buildEncodingTree(int nextFree) {

    MinHeap tree;
    for (int i = 0; i < nextFree; ++i) {
        cout << weightArr[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < nextFree; ++i) {
        if (weightArr[i] > 0) {
            tree.push(i, weightArr);
            tree.display();
        }
    }
    tree.display();
    int numb1;
    int numb2;
    int parent;
    while (tree.size > 1) {
        numb1 = tree.pop(weightArr);
        numb2 = tree.pop(weightArr);

        leftArr[nextFree] = numb1; // left and right pointer assigned
        rightArr[nextFree] = numb2;

        parent = weightArr[numb1] + weightArr[numb2];
        weightArr[nextFree] = parent;
        tree.push(nextFree, weightArr); // fixed this initially pushing the weight of parent and not the index into the minheap
        tree.display();
        nextFree++;
    }
    for (int i = 0; i < nextFree; ++i) {
        cout << weightArr[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < nextFree; ++i) {
        cout << leftArr[i] << " l r " << rightArr[i] << endl;
    }

    return tree.data[0];

}


// generateCodes - We use a stack pair to traverse the tree we made before. With our now full left and right arrays, we can
// check for children and add 0 (left) or 1 (right) to our code
void generateCodes(int root, string codes[]) {

    stack<pair<int, string>> treeStack;
    treeStack.push(make_pair(root, ""));
    pair<int, string> curr; // top of stack, starts at root

    while (!treeStack.empty()) {
        curr = treeStack.top();
        string code = curr.second;
        treeStack.pop();

        // left check for child, adds 0 to code
        if (leftArr[curr.first] != -1) {
            treeStack.push(make_pair(leftArr[curr.first], code + "0"));
        }

        // right check for child, adds 1 to code
        if (rightArr[curr.first] != -1) {
            treeStack.push(make_pair(rightArr[curr.first], code + "1"));
        }

        // check for leaf, records code at current index
        if (leftArr[curr.first] == -1 && rightArr[curr.first] == -1) {
            codes[charArr[curr.first] - 'a'] = code;
        }
    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}
