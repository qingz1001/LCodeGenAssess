#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define INF 1000000000

typedef long long ll;

struct Platform {
    int h, l, r;
};

struct Platform platforms[MAX_N];
int n, h;
ll dp[MAX_N];

int cmp(const void *a, const void *b) {
    return ((struct Platform*)b)->h - ((struct Platform*)a)->h;
}

ll min(ll a, ll b) {
    return a < b ? a : b;
}

ll abs(ll x) {
    return x < 0 ? -x : x;
}

int main() {
    scanf("%d %d", &n, &h);
    int x, y;
    scanf("%d %d", &x, &y);
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &platforms[i].h, &platforms[i].l, &platforms[i].r);
    }
    
    platforms[n].h = 0;
    platforms[n].l = -INF;
    platforms[n].r = INF;
    n++;
    
    qsort(platforms, n, sizeof(struct Platform), cmp);
    
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    
    int current = 0;
    while (platforms[current].h > y) current++;
    
    for (int i = current; i < n; i++) {
        if (i > current && platforms[i-1].h - platforms[i].h > h) break;
        
        ll fall_time = platforms[current].h - platforms[i].h;
        ll left_time = x < platforms[i].l ? platforms[i].l - x : 0;
        ll right_time = x > platforms[i].r ? x - platforms[i].r : 0;
        
        if (x >= platforms[i].l && x <= platforms[i].r) {
            dp[i] = min(dp[i], fall_time);
        } else {
            dp[i] = min(dp[i], fall_time + min(left_time, right_time));
        }
        
        for (int j = current; j < i; j++) {
            ll move_time = min(abs(platforms[i].l - platforms[j].l), abs(platforms[i].l - platforms[j].r));
            move_time = min(move_time, min(abs(platforms[i].r - platforms[j].l), abs(platforms[i].r - platforms[j].r)));
            dp[i] = min(dp[i], dp[j] + fall_time + move_time);
        }
    }
    
    printf("%lld\n", dp[n-1]);
    
    return 0;
}