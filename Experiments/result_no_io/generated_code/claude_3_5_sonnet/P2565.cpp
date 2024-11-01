#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 201
#define MAXM 201

int n, m;
int a[MAXN];
int dice[MAXN][MAXM];
int used[MAXN*MAXM];

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int solve() {
    int i, j, k, num;
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            num = i * m + j + 1;
            for (k = 0; k < n; k++) {
                if (!used[num] && (k == a[i] || (k + 1) % n == i)) {
                    dice[k][j] = num;
                    used[num] = 1;
                    break;
                }
            }
            if (k == n) return 0;
        }
    }
    
    for (i = 0; i < n; i++) {
        qsort(dice[i], m, sizeof(int), compare);
    }
    
    return 1;
}

int main() {
    int i, j;
    
    scanf("%d %d", &n, &m);
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        a[i]--;
    }
    
    memset(used, 0, sizeof(used));
    
    if (solve()) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++) {
                printf("%d ", dice[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("0\n");
    }
    
    return 0;
}