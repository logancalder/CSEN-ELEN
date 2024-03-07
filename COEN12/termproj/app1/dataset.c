// Logan Calder, COEN12L R 9:15, 6/11/2023
/* dataset.c :
    Implements public functions to be used when creating a 2D array set, including adding, removing, & searching
    for an element, obtaining the max age range, and deleting a set. Implements 2D array as data structure as it has same
    big O runtime as hash chaining, but is less memory efficient.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "dataset.h"
#include <stdbool.h>

SET *createSet(int maxElts);
void addElement(SET *sp, int age, int id);
int search(SET *sp, int age);
void removeAge(SET *sp, int age);
int maxAgeGap(SET *sp);
void destroySet(SET *sp);

// createSet O(1)
// ---------------------------------------------------------------------------------------
// Returns a pointer to a new set with a maximum capacity of maxElts
SET *createSet(int maxElts)
{
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->count = 0;
    sp->len = maxElts;
    assert(sp->students != NULL);
    return (sp);
}

// addElement O(n)
// ---------------------------------------------------------------------------------------
// Adds an element to set at first open index.
void addElement(SET *sp, int age, int id)
{
    assert(sp != NULL);
    int i;
    i = 0;
    for (i = 0; i < sp->len; i++)
    {
        if (sp->students[i].age == '\0' || sp->students[i].age == 18)
        {
            sp->students[i].age = age;
            sp->students[i].id = id;
            sp->count++; // Increment count
            return;
        }
    }
    printf("SET IS FULL.\n");
    // Update students 2D array
}

// search O(n)
// ---------------------------------------------------------------------------------------
// Loops through set and returns index if student with age found. Returns -1 if fail.
// Search only returns one student. To utilize with deleting an age range, place in
// while or for loop.
int search(SET *sp, int age)
{
    printf("SEARCHING AGE %i\n", age);
    assert(sp != NULL);
    int i;
    for (i = 0; i < sp->len; i++)
    {
        if (sp->students[i].age == age)
        {
            printf("AGE: %i\nID: %i\nSUCCESSFULLY FOUND\n", sp->students[i].age, sp->students[i].id);
            return i;
        }
    }
    printf("AGE: %i\nID: N/A\nUNSUCCESSFULLY FOUND\n", age);
    return (-1);
}

// removeAge O(n)
// ---------------------------------------------------------------------------------------
// Iterates through set to see if age matches parameter. If so, deletes every student
// with that age in set.
void removeAge(SET *sp, int age)
{
    assert(sp != NULL);
    int index;
    bool wasFound = false;
    for (index = 0; index < sp->len; index++)
    {
        if (sp->students[index].age == age)
        {
            wasFound = true;
            sp->students[index].id = '\0';
            sp->students[index].age = '\0';
            sp->count--;
        }
    }
    if (wasFound)
    {
        printf("SUCCESSFULLY DELETED ALL STUDENTS WITH AGE %i\n", age);
    }
    else
    {
        printf("UNSUCCESSFULLY DELETED: NONE FOUND OF AGE %i\n", age);
    }
}

// maxAgeGap O(n)
// ---------------------------------------------------------------------------------------
// Obtains max and min of set, then returns difference
int maxAgeGap(SET *sp)
{
    assert(sp != NULL);
    int min, max, i;
    min = 30;
    max = 0;
    for (i = 0; i < sp->len; i++)
    {
        if (sp->students[i].age > max)
        {
            max = sp->students[i].age;
        }
        if (sp->students[i].age < min && sp->students[i].age != 0)
        {
            min = sp->students[i].age;
        }
    }
    return (max - min);
}

// destroySet O(1)
// ---------------------------------------------------------------------------------------
// Frees set
void destroySet(SET *sp)
{
    assert(sp != NULL);
    free(sp);
}