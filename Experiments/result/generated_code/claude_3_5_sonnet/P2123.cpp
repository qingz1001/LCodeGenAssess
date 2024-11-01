#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 20000
#define MAX_T 10

typedef long long ll;

typedef struct {
    ll a, b;
} Minister;

int cmp(const void *a, const void *b) {
    Minister *ma = (Minister *)a;
    Minister *mb = (Minister *)b;
    return (mb->a + mb->b) - (ma->a + ma->b);
}

ll max(ll a, ll b) {
    return a > b ? a : b;
}

int main() {
    int T, n;
    Minister ministers[MAX_N];
    
    scanf("%d", &T);
    
    while (T--) {
        scanf("%d", &n);
        
        for (int i = 0; i < n; i++) {
            scanf("%lld %lld", &ministers[i].a, &ministers[i].b);
        }
        
        qsort(ministers, n, sizeof(Minister), cmp);
        
        ll sum = 0, maxReward = 0, reward;
        
        for (int i = 0; i < n; i++) {
            sum += ministers[i].a;
            reward = max(maxReward, sum) + ministers[i].b;
            maxReward = max(maxReward, reward);
        }
        
        printf("%lld\n", maxReward);
    }
    
    return 0;
}