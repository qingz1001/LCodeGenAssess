#include <stdio.h>

int main() {
    int a, b, c, d, p, m, g;
    scanf("%d%d%d%d%d%d%d", &a, &b, &c, &d, &p, &m, &g);

    // Function to determine the state of the dogs
    void checkDogState(int aggressive, int calm, int arrivalTime) {
        int cycleLength = aggressive + calm;
        int cycles = arrivalTime / cycleLength;
        int remainingTime = arrivalTime % cycleLength;

        if (remainingTime <= aggressive) {
            printf("both\n");
        } else if (remainingTime > aggressive && remainingTime <= aggressive + calm) {
            printf("none\n");
        }
    }

    // Check the state of the dogs for each person
    checkDogState(a, b, p);
    checkDogState(a, b, m);
    checkDogState(a, b, g);

    return 0;
}