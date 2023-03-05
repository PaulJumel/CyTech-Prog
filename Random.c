#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Random.h"

int nbRandom(int MAX, int MIN)
{
    int nbRandom;
    nbRandom = (rand() % (MAX - MIN + 1)) + MIN;
    return nbRandom;
}
