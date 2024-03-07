// Logan Calder, COEN12L R 9:15, 6/11/2023
/* college.c:
    Step 1) Utilizes public set functions to create a 2D array 3000 in length, randomly generate 1000 unique students, and append them
    into a set.

    Step 2) Then randomly generates a student age, and removes all students of that age from set if found.

    Step 3) Obtains the max and min ages for set, and prints the age difference

    Step 4) Destroys the set, freeing all memory that can be freed.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "dataset.h"
#include <time.h>

int main(void)
{
    // PART 1
    // Creating a set of 1000 students w/ ID and age generation

    SET *uni = createSet(3000);

    time_t t;
    srand((unsigned)time(&t));

    int i, age, id, idPrev;
    idPrev = 0;
    for (i = 0; i < 1000; i++)
    {
        age = (rand() % (30 - 18 + 1)) + 18; // Generate age 18-30
        id = (rand() % 2) + 1;
        idPrev += id;
        addElement(uni, age, idPrev);
    }

    // PART 2
    // Randomly generating a student record w/ ID from 00001 ~ 2000 & age 18~30. Then delete if exists.

    age = (rand() % (30 - 18 + 1)) + 18; // Generate age 18-30
    printf("\nGEN AGE: %i\n", age);
    removeAge(uni, age);

    // PART 3
    // Obtain max age gap and print out the value

    printf("\nMaximum Age Gap: %i\n", maxAgeGap(uni));

    // PART 4
    // Destroy set

    destroySet(uni);

    return (0);
}