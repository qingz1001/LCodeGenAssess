#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200001
#define MAX_M 200001

int n, m;
int a[MAX_N];
int x[MAX_M], y[MAX_M];
int max_x = 0;

int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x[i], &y[i]);
        if (x[i] > max_x) max_x = x[i];
    }
    
    qsort(a + 1, n, sizeof(int), compare);
    
    long long cost = 0;
    int turn_point = 0;
    
    for (int i = 1; i <= max_x; i++) {
        if (turn_point < m && i == x[turn_point]) {
            cost += a[i];
            turn_point++;
        }
    }
    
    printf("%lld\n", cost);
    
    return 0;
}