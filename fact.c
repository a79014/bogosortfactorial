#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>


bool is_sorted(int *a, int n)
{
    while (--n >= 1)
    {
        if (a[n] < a[n - 1])
            return false;
    }
    return true;
}

void shuffle(int *a, int n)
{
    int i, t, r;
    for (i = 0; i < n; i++)
    {
        t = a[i];
        r = rand() % n;
        a[i] = a[r];
        a[r] = t;
    }
}

double bogosort(int *a, int n)
{
    double count = 0;
    while (!is_sorted(a, n))
    {   
        count++;
        shuffle(a, n);
    }
    return count;
}


//I should've used unsigned long numbers instead of int... but 
//who is gonna try to find the factorial of 60 using this? N-not me eh-heh... eh yeah...
int main(int argc, char **argv)
{

    printf("Don't tell your parents you did this\n");
    //get a new seed each time the program is ran
    srand(time(NULL));

    //size is actually the number you want to know the factorial of
    //atoi turns a string into a number
    int size = atoi(argv[1]);
    if(size < 0) {
        printf("Converting %d to %d (only positive numbers are supported right now)\n", size, size*-1);
        size *= -1;
    }


    int i = 0;
    //array of the size of the number you want to know the factorial of
    //no one got time fo free(); beware memory leaks
    int *elements = malloc(sizeof(int) * size);

    // inizialize sorted array
    for (i = 0; i < size; ++i)
        elements[i] = i;

    //code-y part next!!

    //I decided that just re-randomizing the array after each cycle was enough
    //so I nested the for cycle to bogo-sort 10 times inside the cycle that randomly
    //shuffles the items. edit: the other way around, bogo for is outer, random for is inner

    /*
    IMPORTANT MATH: averageNEW = averageOLD + (valueNEW-averageOLD)/sizeNEW
    */

    int j = 0;
    double avgNew = 0, avgOld = 0, valueNew = 0, sizeNew = 0;
    //do the sorting N times
    for (j = 0; j < 1000; j++)
    {   
        //47 is a prime, close to 50, so that it will only tell you which cycle it is on every 47 times. Prevents spam
        //!(j%47) means that j%47 is 0
        //comment if you want to see detailed "progress"
        if(!(j%47))
            printf("Cycle %d...\n", j);
        //randomize the sorted array
        for (i = size - 1; i > 0; --i)
        {
            // generate random index
            int w = rand() % i;
            // swap items
            int t = elements[i];
            elements[i] = elements[w];
            elements[w] = t;
        }
        valueNew = bogosort(elements, size);
        //sizeNew is basically the number of elements in an average. avg of 2 and 4 is 3, sizeNew would be 2, because there were 2 numbers
        sizeNew++;
        //get new average
        avgNew = avgOld + (valueNew - avgOld)/sizeNew;
        //avgNew is gonna change next cycle, gotta put it somewhere :^)
        avgOld = avgNew;
    }

    printf("the factorial of %d is roughly %d \n", size, (int)avgOld);
    free(elements);
    return 0;
}