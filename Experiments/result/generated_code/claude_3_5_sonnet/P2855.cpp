#include <stdio.h>
#include <stdlib.h>

#define MAX_N 50000

int L, N, M;
int rocks[MAX_N + 2];

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int check(int dist) {
    int count = 0, prev = 0;
    for (int i = 1; i <= N + 1; i++) {
        if (rocks[i] - prev < dist) {
            count++;
        } else {
            prev = rocks[i];
        }
    }
    return count <= M;
}

int binary_search() {
    int left = 1, right = L, mid;
    while (left < right) {
        mid = left + (right - left + 1) / 2;
        if (check(mid)) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }
    return left;
}

int main() {
    scanf("%d %d %d", &L, &N, &M);
    
    rocks[0] = 0;
    for (int i = 1; i <= N; i++) {
        scanf("%d", &rocks[i]);
    }
    rocks[N + 1] = L;
    
    qsort(rocks, N + 2, sizeof(int), compare);
    
    printf("%d\n", binary_search());
    
    return 0;
}