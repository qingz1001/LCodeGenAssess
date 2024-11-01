#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100000
#define MAX_M 100000

int n, m;
long long w[MAX_N], m_weights[MAX_M];
int count[MAX_M];

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
    
    int j = 0;
    for (int i = 0; i < m; i++) {
        while (j < m && m_weights[j] <= m_weights[i]) {
            count[i]++;
            j++;
        }
    }
    
    int result = 0;
    j = m - 1;
    
    for (int i = n - 1; i >= 0; i--) {
        while (j >= 0 && m_weights[j] > w[i]) {
            j--;
        }
        if (j >= 0) {
            result += count[j];
            w[i] = 0;
        }
    }
    
    printf("%d\n", result);
    
    return 0;
}