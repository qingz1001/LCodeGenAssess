#include <stdio.h>
#include <string.h>

#define MAX_N 30001
#define MAX_M 5001

int n, m;
int diff[MAX_N];
int need[MAX_N];

int main() {
    scanf("%d %d", &n, &m);
    
    memset(diff, 0, sizeof(diff));
    memset(need, 0, sizeof(need));
    
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        need[a] = (need[a] > c) ? need[a] : c;
        need[b+1] = (need[b+1] > -c) ? need[b+1] : -c;
    }
    
    int cur = 0, res = 0;
    for (int i = 1; i <= n; i++) {
        cur += need[i];
        diff[i] = (cur > diff[i-1]) ? cur : diff[i-1];
        res = (res > diff[i]) ? res : diff[i];
    }
    
    printf("%d\n", res);
    
    return 0;
}