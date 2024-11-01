#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000001

int n, m;
int rooms[MAX_N];
int diff[MAX_N];

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
        
        int sum = 0;
        for (int j = s; j <= t; j++) {
            sum += diff[j];
            if (sum > rooms[j]) {
                printf("-1\n%d\n", i);
                return 0;
            }
        }
    }
    
    printf("0\n");
    return 0;
}