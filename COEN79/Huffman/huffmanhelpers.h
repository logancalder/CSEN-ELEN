/*
 * Name: Logan Calder
 * Email: lcalder@scu.edu
 * Contact: 4085946314
 *
 * Assignment: Final
 * 4 of 5: huffmanhelpers.cxx, huffmannode.cxx, main.cxx,
 *         huffmanhelpers.h, huffmannode.h
 */
#ifndef HUFFMAN_HELPERS_H
#define HUFFMAN_HELPERS_H

#include <string>
#include <map>

struct HuffmanNode;

struct CompareNodes
{
    bool operator()(HuffmanNode *lhs, HuffmanNode *rhs);
};

std::map<char, int> getCharacterFrequencies(const std::string &content);

HuffmanNode *buildHuffmanTree(std::map<char, int> &frequencyMap);

void generateHuffmanCodes(HuffmanNode *root, std::string code, std::map<char, std::string> &huffmanCodes, int &totalBits);

#endif // HUFFMAN_HELPERS_H
