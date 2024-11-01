#include <stdio.h>

int main() {
    int A, B, C;
    char order[4];

    scanf("%d %d %d", &A, &B, &C);
    scanf("%s", order);

    if (order[0] == 'A') {
        if (order[1] == 'B') {
            if (order[2] == 'C') {
                printf("%d %d %d\n", A, B, C);
            } else if (order[2] == 'A') {
                printf("%d %d %d\n", C, A, B);
            } else {
                printf("%d %d %d\n", A, C, B);
            }
        } else {
            if (order[2] == 'B') {
                printf("%d %d %d\n", A, C, B);
            } else if (order[2] == 'A') {
                printf("%d %d %d\n", C, A, B);
            } else {
                printf("%d %d %d\n", A, B, C);
            }
        }
    } else if (order[0] == 'B') {
        if (order[1] == 'A') {
            if (order[2] == 'C') {
                printf("%d %d %d\n", B, A, C);
            } else if (order[2] == 'B') {
                printf("%d %d %d\n", B, C, A);
            } else {
                printf("%d %d %d\n", A, B, C);
            }
        } else {
            if (order[2] == 'B') {
                printf("%d %d %d\n", B, C, A);
            } else if (order[2] == 'A') {
                printf("%d %d %d\n", C, A, B);
            } else {
                printf("%d %d %d\n", A, B, C);
            }
        }
    } else {
        if (order[1] == 'A') {
            if (order[2] == 'B') {
                printf("%d %d %d\n", C, A, B);
            } else if (order[2] == 'C') {
                printf("%d %d %d\n", C, B, A);
            } else {
                printf("%d %d %d\n", A, B, C);
            }
        } else {
            if (order[2] == 'B') {
                printf("%d %d %d\n", C, B, A);
            } else if (order[2] == 'A') {
                printf("%d %d %d\n", C, A, B);
            } else {
                printf("%d %d %d\n", A, B, C);
            }
        }
    }

    return 0;
}