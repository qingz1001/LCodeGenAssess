#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 500000

int N, K;
int p[MAX_N], c[MAX_N];
bool must[MAX_N + 1];

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    scanf("%d %d", &N, &K);
    
    for (int i = 0; i < K; i++) {
        scanf("%d", &p[i]);
        must[p[i]] = true;
    }
    
    for (int i = 1; i <= N; i++) {
        scanf("%d", &c[i]);
    }
    
    qsort(p, K, sizeof(int), compare);
    
    int last = 0, count = 0;
    bool possible = true;
    
    for (int i = 0; i < K; i++) {
        int day = p[i];
        if (c[day] <= last) {
            possible = false;
            break;
        }
        last = c[day];
        count++;
    }
    
    if (!possible) {
        printf("impossible\n");
        return 0;
    }
    
    for (int i = 1; i <= N; i++) {
        if (must[i]) continue;
        if (c[i] > last) {
            last = c[i];
            count++;
        }
    }
    
    printf("%d\n", count);
    
    return 0;
}