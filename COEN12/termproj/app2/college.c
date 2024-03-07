// Logan Calder, COEN12L R 9:15, 6/11/2023
/* college.c:
    Step 1) Utilizes public set functions to create a hash table 3001 in length (nearest prime #), randomly generate 1000 unique students,
    and append them into the table.

    Step 2) Then randomly generates a student id, and removes the student with that ID, if found.

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

    SET *uni = createSet(3001);

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

    id = (rand() % (2000 - 1 + 1)) + 1; // Generate id 1-2000
    printf("\nGEN ID: %i\n", id);
    removeID(uni, id);

    // PART 3
    // Destroy set

    destroySet(uni);

    return (0);
}