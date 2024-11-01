#include <stdio.h>
#include <stdlib.h>

#define MAX_N 5000
#define MAX_S 1000000

int cows[MAX_N];

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &cows[i]);
    }

    qsort(cows, N, sizeof(int), compare);

    int max_diff = 0;
    for (int i = 1; i < N; i++) {
        int diff = cows[i] - cows[i - 1];
        if (diff > max_diff) {
            max_diff = diff;
        }
    }

    int result = max_diff;
    for (int i = 1; i < N; i++) {
        result = gcd(result, cows[i] - cows[i - 1]);
    }

    printf("%d\n", result);
    return 0;
}