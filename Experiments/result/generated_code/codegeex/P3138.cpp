#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000
#define MAX_COORD 1000000

int count[MAX_COORD + 1];

int main() {
    int N;
    scanf("%d", &N);

    memset(count, 0, sizeof(count));

    for (int i = 0; i < N; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        count[x]++;
        count[y]++;
    }

    int min_max = MAX_N;
    for (int a = 1; a <= MAX_COORD; a += 2) {
        int max = 0;
        for (int i = a - 1; i <= a + 1; i += 2) {
            max = (count[i] > max) ? count[i] : max;
        }
        min_max = (max < min_max) ? max : min_max;
    }

    printf("%d\n", min_max);

    return 0;
}