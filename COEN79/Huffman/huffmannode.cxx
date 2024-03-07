/*
 * Name: Logan Calder
 * Email: lcalder@scu.edu
 * Contact: 4085946314
 *
 * Assignment: Final
 * 2 of 5: huffmanhelpers.cxx, huffmannode.cxx, main.cxx,
 *         huffmanhelpers.h, huffmannode.h
 */
#include "huffmannode.h"

HuffmanNode::HuffmanNode(char ch, int freq) : data(ch), frequency(freq), left(nullptr), right(nullptr) {}
