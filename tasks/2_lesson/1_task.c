#include <stdio.h>

int main(void)
{
    int numBottles, numExchange;
    int numDrunk = 0;

    if (scanf("%d %d", &numBottles, &numExchange) != 2) {
        return 1;
    }

    while (numBottles >= numExchange) {
        int newBottles = numBottles / numExchange;

        numDrunk += newBottles * numExchange;
        numBottles = numBottles % numExchange + newBottles;
    }

    numDrunk += numBottles;

    printf("%d\n", numDrunk);

    return 0;
}
