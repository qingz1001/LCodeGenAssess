#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 1000005
#define INF 0x3f3f3f3f

int n, s;
int l[MAXN], d[105];
int sum[MAXN], f[MAXN];

int main() {
    scanf("%d%d", &n, &s);
    
    for(int i = 1; i <= n; i++) {
        scanf("%d", &l[i]);
        sum[i] = sum[i-1] + l[i];
    }
    
    for(int i = 1; i <= s; i++) {
        scanf("%d", &d[i]);
    }
    
    for(int k = 1; k <= s; k++) {
        if(d[k] >= sum[n]) {
            printf("2\n");
            continue;
        }
        
        if(d[k] < *max_element(l+1, l+n+1)) {
            printf("NIE\n");
            continue;
        }
        
        memset(f, 0x3f, sizeof(f));
        f[0] = 0;
        
        for(int i = 1; i <= n; i++) {
            for(int j = i-1; j >= 0; j--) {
                if(sum[i] - sum[j] > d[k]) break;
                f[i] = (f[i] < f[j]+1) ? f[i] : (f[j]+1);
            }
        }
        
        int ans = INF;
        for(int i = 0; i < n; i++) {
            int tmp = f[i] + f[n] - f[i];
            if(sum[n] - sum[i] + sum[n-1] <= d[k]) tmp--;
            ans = (ans < tmp) ? ans : tmp;
        }
        
        printf("%d\n", ans);
    }
    
    return 0;
}