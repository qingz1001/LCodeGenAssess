#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20000
#define MAX_K 50000
#define MAX_C 100

typedef struct {
    int start;
    int end;
    int count;
} Group;

int main() {
    int K, N, C;
    scanf("%d %d %d", &K, &N, &C);

    Group groups[MAX_K];
    for (int i = 0; i < K; ++i) {
        scanf("%d %d %d", &groups[i].start, &groups[i].end, &groups[i].count);
    }

    int max_cows = 0;
    for (int i = 0; i < K; ++i) {
        if (groups[i].count > C) {
            max_cows += C;
        } else {
            max_cows += groups[i].count;
        }
    }

    printf("%d\n", max_cows);

    return 0;
}