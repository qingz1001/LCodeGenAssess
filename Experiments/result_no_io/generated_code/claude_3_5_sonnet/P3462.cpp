#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100000
#define MAX_M 100000

int n, m;
long long w[MAX_N], m_weights[MAX_M];

int cmp(const void *a, const void *b) {
    return *(long long*)a - *(long long*)b;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        scanf("%lld", &w[i]);
    }
    
    for (int i = 0; i < m; i++) {
        scanf("%lld", &m_weights[i]);
    }
    
    qsort(w, n, sizeof(long long), cmp);
    qsort(m_weights, m, sizeof(long long), cmp);
    
    int result = 0;
    int j = 0;
    long long current_sum = 0;
    
    for (int i = 0; i < n; i++) {
        while (j < m && current_sum + m_weights[j] <= w[i]) {
            current_sum += m_weights[j];
            j++;
            result++;
        }
        current_sum = 0;
    }
    
    printf("%d\n", result);
    
    return 0;
}