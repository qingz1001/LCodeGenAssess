#include <stdio.h>
#include <stdlib.h>

#define MAX_N 5000

int main() {
    int N;
    scanf("%d", &N);
    int prices[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &prices[i]);
    }

    int maxBuys = 0;
    int count = 0;

    for (int i = 1; i < N; i++) {
        if (prices[i] < prices[i - 1]) {
            maxBuys++;
        }
    }

    printf("%d %d\n", maxBuys, count);

    return 0;
}