#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000001
#define MAX_M 2004

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int paintings[MAX_N];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &paintings[i]);
    }
    
    int first[MAX_M] = {0}, last[MAX_M] = {0};
    for (int i = 0; i < n; ++i) {
        if (first[paintings[i]] == 0) {
            first[paintings[i]] = i + 1;
        }
        last[paintings[i]] = i + 1;
    }
    
    int min_cost = n;
    int best_a = 0, best_b = 0;
    
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (last[i] >= first[j]) {
                int cost = last[i] - first[j] + 1;
                if (cost < min_cost || (cost == min_cost && first[j] < best_a)) {
                    min_cost = cost;
                    best_a = first[j];
                    best_b = last[i];
                }
            }
        }
    }
    
    printf("%d %d\n", best_a, best_b);
    
    return 0;
}