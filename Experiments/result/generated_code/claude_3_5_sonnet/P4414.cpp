#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int a, b, c;
    char order[4];

    scanf("%d %d %d", &a, &b, &c);
    scanf("%s", order);

    if (a > b) swap(&a, &b);
    if (b > c) swap(&b, &c);
    if (a > b) swap(&a, &b);

    for (int i = 0; i < 3; i++) {
        if (order[i] == 'A') printf("%d ", a);
        else if (order[i] == 'B') printf("%d ", b);
        else if (order[i] == 'C') printf("%d ", c);
    }

    return 0;
}