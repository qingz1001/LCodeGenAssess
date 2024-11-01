#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    
    int* r = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &r[i]);
    }
    
    int* d = (int*)malloc(m * sizeof(int));
    int* s = (int*)malloc(m * sizeof(int));
    int* t = (int*)malloc(m * sizeof(int));
    
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &d[i], &s[i], &t[i]);
    }
    
    int* delta = (int*)calloc(n, sizeof(int));
    
    for (int i = 0; i < m; i++) {
        delta[s[i] - 1] += d[i];
        if (t[i] < n) {
            delta[t[i]] -= d[i];
        }
    }
    
    int current = 0;
    for (int i = 0; i < n; i++) {
        current += delta[i];
        if (current > r[i]) {
            printf("-1\n%d\n", i + 1);
            free(r);
            free(d);
            free(s);
            free(t);
            free(delta);
            return 0;
        }
    }
    
    printf("0\n");
    free(r);
    free(d);
    free(s);
    free(t);
    free(delta);
    return 0;
}