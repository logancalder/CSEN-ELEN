/*
 * Name: Logan Calder
 * Email: lcalder@scu.edu
 * Contact: 4085946314
 *
 * Assignment: Final
 * 5 of 5: huffmanhelpers.cxx, huffmannode.cxx, main.cxx,
 *         huffmanhelpers.h, huffmannode.h
 */
#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

struct HuffmanNode
{
    char data;
    int frequency;
    HuffmanNode *left;
    HuffmanNode *right;

    HuffmanNode(char ch, int freq);
};

#endif // HUFFMAN_NODE_H
