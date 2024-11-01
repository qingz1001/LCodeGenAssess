#include <stdio.h>

int main() {
    int a, b, c, d, p, m, g;
    scanf("%d %d %d %d %d %d %d", &a, &b, &c, &d, &p, &m, &g);

    // Function to determine the state of the dogs at a given time
    void checkDogs(int time, int a, int b, int c, int d) {
        int dog1 = time % (a + b);
        int dog2 = time % (c + d);

        if (dog1 < a && dog2 < c) {
            printf("both\n");
        } else if (dog1 < a || dog2 < c) {
            printf("one\n");
        } else {
            printf("none\n");
        }
    }

    // Check the state of the dogs for each person
    checkDogs(p, a, b, c, d);
    checkDogs(m, a, b, c, d);
    checkDogs(g, a, b, c, d);

    return 0;
}