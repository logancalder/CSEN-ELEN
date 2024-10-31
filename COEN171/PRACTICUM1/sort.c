// Name: Logan Calder
// Date: 10/12/2024
// Title: Practicum 1 – 2.1: QuickSort (C)

#include <stdio.h>

#define HIGH 8

typedef int numbers[HIGH];

numbers a; // a HIGH large with type numbers

typedef int (*comparator)(int x, int y);

void readarray(void)
{
    for (int i = 0; i < HIGH; i++)
    {
        scanf("%d", &a[i]);
    }
    return;
}

void writearray(void)
{
    for (int i = 0; i < HIGH; i++)
    {
        printf("%d\n", a[i]);
    }
    return;
}

static void exchange(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
    return;
}

static int partition(numbers a, int y, int z)
{
    int i, j, x;

    x = a[y];
    i = y - 1;
    j = z + 1;

    while (i < j)
    {
        do
        {
            j--;
        } while (a[j] > x);

        do
        {
            i++;
        } while (a[i] < x);

        if (i < j)
        {
            exchange(&a[i], &a[j]);
        }
    }

    return j;
}

int compare(int x, int y)
{
    if (x > y)
    {
        return 1;
    }
    else if (x == y)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}
// void quicksort(numbers a, int m, int n)
void quicksort(numbers a, int m, int n)
{
    int i;
    comparator cmp = compare;

    if (cmp(m, n) < 0)
    {
        i = partition(a, m, n);
        quicksort(a, m, i);
        quicksort(a, i + 1, n);
    }
    return;
}

int main(void)
{
    readarray();
    quicksort(a, 0, HIGH - 1);
    writearray();

    return 1;
}