#ifndef APP2_H
#define APP2_H

typedef struct student
{
    int age;
    int id;
} STUDENT;

typedef struct set
{
    STUDENT students[3000];
    int len;
    int count;
} SET;

SET *createSet(int maxElts);

void addElement(SET *sp, int age, int id);

int search(SET *sp, int age);

void removeAge(SET *sp, int age);

int maxAgeGap(SET *sp);

void destroySet(SET *sp);

#endif /* APP2_H */
