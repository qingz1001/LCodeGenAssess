#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10
#define MAX_J 20

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int N, M, J;
    int apples[MAX_J];
    int left = 1, right, moves = 0;

    scanf("%d %d", &N, &M);
    scanf("%d", &J);

    for (int i = 0; i < J; i++) {
        scanf("%d", &apples[i]);
    }

    right = M;

    for (int i = 0; i < J; i++) {
        if (apples[i] < left) {
            moves += left - apples[i];
            right -= left - apples[i];
            left = apples[i];
        } else if (apples[i] > right) {
            moves += apples[i] - right;
            left += apples[i] - right;
            right = apples[i];
        }
    }

    printf("%d\n", moves);

    return 0;
}