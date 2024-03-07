// Logan Calder, COEN12L R 9:15, 6/8/23
// Script implements huffman encoding (compression system) utilizing pqueue.c and pack.c. Has functions to create a new node, compare
// two nodes, find the # of bits in a node, and the main function for the huffman algorithim. Will accept a text file as a parameter
// and print out the # of bits per letter. Then calculates total bits used from compression.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pqueue.h"
#include "pack.h"
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define NODE struct node // Defining a node structure to be used as NODE

// Defining mknode, which is a private function used to  make a new node. No children for last gen nodes.
// ---------------------------------------------------------------------------------------
NODE *mknode(int count, NODE *left_node, NODE *right_node)
{
    NODE *new_node = malloc(sizeof(NODE));
    assert(new_node != NULL);
    new_node->count = count;
    new_node->parent = NULL;
    if (left_node != NULL)
    {
        left_node->parent = new_node;
    }
    if (right_node != NULL)
    {
        right_node->parent = new_node;
    }
    return (new_node);
}

// Defining cmp to compare two nodes. Each return condition is listed in if statements below.
// ---------------------------------------------------------------------------------------
int cmp(NODE *t1, NODE *t2)
{
    if (t1->count < t2->count)
        return (-1);
    if (t1->count > t2->count)
        return (1);
    if (t1->count == t2->count)
        return (0);
}

// Defining depth to calculate the # of bits in a node
// ---------------------------------------------------------------------------------------
int depth(NODE *node)
{
    if (node->parent == NULL)
    {
        return (0);
    }
    else
    {
        return 1 + depth(node->parent);
    }
}

// Main function to implement and print out huffman compression values
// ---------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    // Part 1
    if (argc != 3)
    {
        return 0;
    }

    int counts[257];
    NODE *nodes[257];

    int i;
    for (i = 0; i < 257; i++)
    {
        counts[i] = 0;
        nodes[i] = NULL;
    }

    // Part 2

    FILE *fp = fopen(argv[1], "rb");
    assert(fp != NULL);

    int j;
    while ((j = getc(fp)) != EOF)
    {
        counts[j]++;
    }
    fclose(fp);

    PQ *pq = createQueue(*cmp);
    for (i = 0; i < 257; i++)
    {
        if (counts[i] > 0)
        {
            nodes[i] = mknode(counts[i], NULL, NULL);
            addEntry(pq, nodes[i]);
        }
    }

    // Part 3

    NODE *end = malloc(sizeof(NODE));
    assert(end != NULL);
    end->parent = NULL;
    end->count = 0;
    nodes[256] = end;
    addEntry(pq, nodes[256]);

    // Part 4

    while (numEntries(pq) > 1)
    {
        NODE *l = removeEntry(pq);
        NODE *r = removeEntry(pq);
        NODE *p = mknode(r->count + l->count, l, r);
        addEntry(pq, p);
    }

    // Part 5

    int bits, totalBits;
    totalBits = 0;
    for (i = 0; i < 257; i++)
    {
        if (nodes[i] != NULL)
        {
            bits = depth(nodes[i]);
            if (isprint(i) == false)
            {
                printf("%03o: %d x %d bits = %d bits\n", i, counts[i], bits, counts[i] * bits);
            }
            else
            {
                printf("'%c': %d x %d bits = %d bits\n", i, counts[i], bits, counts[i] * bits);
            }
        }
    }
    pack(argv[1], argv[2], nodes);
}