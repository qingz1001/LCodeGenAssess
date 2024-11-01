#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000001

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    long long *rooms = (long long *)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        scanf("%lld", &rooms[i]);
    }
    
    int *orders = (int *)malloc(m * 3 * sizeof(int));
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &orders[i * 3], &orders[i * 3 + 1], &orders[i * 3 + 2]);
    }
    
    for (int i = 0; i < m; i++) {
        int d = orders[i * 3];
        int s = orders[i * 3 + 1];
        int t = orders[i * 3 + 2];
        
        int satisfied = 1;
        for (int j = s - 1; j <= t - 1; j++) {
            if (rooms[j] < d) {
                satisfied = 0;
                break;
            }
            rooms[j] -= d;
        }
        
        if (!satisfied) {
            printf("-1\n%d\n", i + 1);
            return 0;
        }
    }
    
    printf("0\n");
    free(rooms);
    free(orders);
    return 0;
}