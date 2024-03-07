/*
 * Name: Logan Calder
 * Email: lcalder@scu.edu
 * Contact: 4085946314
 *
 * Assignment: Final
 * 1 of 5: huffmanhelpers.cxx, huffmannode.cxx, main.cxx,
 *         huffmanhelpers.h, huffmannode.h
 */

#include "huffmanhelpers.h"
#include "huffmannode.h"
#include <queue>

using namespace std;

bool CompareNodes::operator()(HuffmanNode *lhs, HuffmanNode *rhs)
{
    return lhs->frequency > rhs->frequency;
}

map<char, int> getCharacterFrequencies(const string &content)
{
    map<char, int> frequencyMap;
    for (char c : content)
    {
        if (isprint(c) || c == '\n')
        {
            frequencyMap[c]++;
        }
    }
    return frequencyMap;
}

HuffmanNode *buildHuffmanTree(map<char, int> &frequencyMap)
{
    priority_queue<HuffmanNode *, vector<HuffmanNode *>, CompareNodes> pq;

    for (const auto &pair : frequencyMap)
    {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    while (pq.size() > 1)
    {
        HuffmanNode *left = pq.top();
        pq.pop();

        HuffmanNode *right = pq.top();
        pq.pop();

        HuffmanNode *newNode = new HuffmanNode('\0', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        pq.push(newNode);
    }

    return pq.top();
}

void generateHuffmanCodes(HuffmanNode *root, string code, map<char, string> &huffmanCodes, int &totalBits)
{
    if (!root)
    {
        return;
    }

    if (!root->left && !root->right)
    {
        huffmanCodes[root->data] = code;
        totalBits += code.length() * root->frequency;
        return;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes, totalBits);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes, totalBits);
}
