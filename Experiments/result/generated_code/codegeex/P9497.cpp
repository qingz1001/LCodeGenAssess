#include <stdio.h>
#include <stdlib.h>

#define MAXN 1001

int cmp(const void *a, const void *b) {
    return *(int*)b - *(int*)a;
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    
    int a[MAXN][MAXN];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    
    for (int i = 0; i < n; i++) {
        qsort(a[i], n, sizeof(int), cmp);
    }
    
    while (q--) {
        int v;
        scanf("%d", &v);
        
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (a[i][j] >= v) {
                    ans++;
                    break;
                }
            }
        }
        
        printf("%d\n", ans);
    }
    
    return 0;
}