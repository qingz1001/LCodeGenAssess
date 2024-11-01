#include <stdio.h>
#include <string.h>

#define MAX_N 1005
#define MAX_K 1005

int n, m, k;
int a[MAX_N][MAX_N];
int count[MAX_K];

int main() {
    scanf("%d %d %d", &n, &m, &k);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    
    memset(count, 0, sizeof(count));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            count[a[i][j] - 1]++;
        }
    }
    
    for (int i = 0; i < k; i++) {
        printf("%d ", count[i]);
    }
    
    return 0;
}