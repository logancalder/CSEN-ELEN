/*
 * Name: Logan Calder
 * Email: lcalder@scu.edu
 * Contact: 4085946314
 *
 * Assignment: Final
 * 3 of 5: huffmanhelpers.cxx, huffmannode.cxx, main.cxx,
 *         huffmanhelpers.h, huffmannode.h
 */
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <iterator>
#include "huffmannode.h"
#include "huffmanhelpers.h"

using namespace std;

int main(int argc, char *argv[])
{
    std::string fn;
    if (argc > 1)
        fn = argv[1];
    else
        cerr << "Need a file name" << endl;

    ifstream file(fn);
    if (!file.is_open())
    {
        cerr << "Error opening file." << endl;
        return 1;
    }

    // Read the content of the file
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    // Perform frequency analysis
    map<char, int> frequencyMap = getCharacterFrequencies(content);

    // Build the Huffman tree
    HuffmanNode *root = buildHuffmanTree(frequencyMap);

    // Generate Huffman codes
    map<char, string> huffmanCodes;
    int totalBits = 0;
    generateHuffmanCodes(root, "", huffmanCodes, totalBits);

    // Create a vector of pairs to sort codes by length
    vector<pair<char, string>> sortedCodes(huffmanCodes.begin(), huffmanCodes.end());
    sort(sortedCodes.begin(), sortedCodes.end(), [](const auto &a, const auto &b)
         { return a.second.length() < b.second.length(); });

    // Print the results in ascending order of the code length
    for (const auto &pair : sortedCodes)
    {
        char c = pair.first;
        int frequency = frequencyMap[c];
        string code = pair.second;
        int codeLength = code.length();

        cout << fixed << setprecision(4) << (static_cast<double>(frequency) / content.length()) * 100 << "% (\"";
        if (isprint(c))
        {
            cout << c << "\" ";
        }
        else
        {
            cout << "\\x" << hex << (unsigned int)c << " ";
        }
        cout << code << ", length=" << dec << codeLength << ")" << endl;
    }

    // Clean up memory
    file.close();
    delete root;

    return 0;
}
