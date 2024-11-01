#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 20000
#define INF 0x3f3f3f3f3f3f3f3fLL

typedef long long ll;

struct Minister {
    ll a, b;
};

int cmp(const void *a, const void *b) {
    return ((struct Minister *)a)->a - ((struct Minister *)b)->a;
}

ll max(ll a, ll b) {
    return a > b ? a : b;
}

ll solve(struct Minister *ministers, int n) {
    qsort(ministers, n, sizeof(struct Minister), cmp);
    
    ll sum = 0;
    ll maxReward = -INF;
    ll prevReward = 0;
    
    for (int i = n - 1; i >= 0; i--) {
        sum += ministers[i].a;
        ll currentReward = max(prevReward, sum) + ministers[i].b;
        maxReward = max(maxReward, currentReward);
        prevReward = currentReward;
    }
    
    return maxReward;
}

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        int n;
        scanf("%d", &n);
        
        struct Minister ministers[MAX_N];
        for (int i = 0; i < n; i++) {
            scanf("%lld %lld", &ministers[i].a, &ministers[i].b);
        }
        
        ll result = solve(ministers, n);
        printf("%lld\n", result);
    }
    
    return 0;
}