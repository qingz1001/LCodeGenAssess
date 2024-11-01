#include <stdio.h>
#include <stdlib.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);

    int min_pos = (a < b) ? a : b;
    int max_pos = (a > b) ? a : b;

    int steps;

    if (min_pos >= 0) {
        steps = max_pos;
    } else if (max_pos <= 0) {
        steps = -min_pos;
    } else {
        int option1 = max_pos - min_pos;
        int option2 = abs(min_pos) + abs(max_pos);
        steps = (option1 < option2) ? option1 : option2;
    }

    printf("%d\n", steps);

    return 0;
}