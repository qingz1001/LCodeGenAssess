#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000005

int n, m;
int rooms[MAXN];
long long diff[MAXN];

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &rooms[i]);
    }
    
    for (int i = 1; i <= m; i++) {
        int d, s, t;
        scanf("%d %d %d", &d, &s, &t);
        
        diff[s] += d;
        diff[t+1] -= d;
        
        long long occupied = 0;
        for (int j = 1; j <= n; j++) {
            occupied += diff[j];
            if (occupied > rooms[j]) {
                printf("-1\n%d\n", i);
                return 0;
            }
        }
    }
    
    printf("0\n");
    return 0;
}