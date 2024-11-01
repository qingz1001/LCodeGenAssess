#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct {
    int a, b, c;
} State;

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int is_same_state(State s1, State s2) {
    int arr1[3] = {s1.a, s1.b, s1.c};
    int arr2[3] = {s2.a, s2.b, s2.c};
    qsort(arr1, 3, sizeof(int), cmp);
    qsort(arr2, 3, sizeof(int), cmp);
    return memcmp(arr1, arr2, sizeof(arr1)) == 0;
}

int min_moves(State start, State end) {
    int moves = 0;
    while (!is_same_state(start, end)) {
        int d1 = start.b - start.a;
        int d2 = start.c - start.b;
        if (d1 == d2) return -1; // No solution
        if (d1 < d2) {
            int jump = MIN(d2 / 2, d2 - d1);
            start.a += jump;
            start.b += jump;
        } else {
            int jump = MIN(d1 / 2, d1 - d2);
            start.b -= jump;
            start.c -= jump;
        }
        moves++;
    }
    return moves;
}

int main() {
    State start, end;
    scanf("%d %d %d", &start.a, &start.b, &start.c);
    scanf("%d %d %d", &end.a, &end.b, &end.c);

    qsort(&start, 1, sizeof(State), (int (*)(const void *, const void *))cmp);
    qsort(&end, 1, sizeof(State), (int (*)(const void *, const void *))cmp);

    int result = min_moves(start, end);
    if (result == -1) {
        printf("NO\n");
    } else {
        printf("YES\n%d\n", result);
    }

    return 0;
}