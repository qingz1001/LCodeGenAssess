#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

typedef long long ll;

ll parent[MAX_N + 1];
ll birth[MAX_N + 1];

void init() {
    parent[1] = 0;
    birth[1] = 1;
    parent[2] = 1;
    birth[2] = 2;
    
    ll p = 1, q = 2, r = 3;
    while (r <= MAX_N) {
        parent[r] = p;
        birth[r] = birth[p] + 1;
        p = q;
        q = r;
        r++;
    }
}

ll find_lca(ll a, ll b) {
    while (a != b) {
        if (birth[a] > birth[b]) {
            a = parent[a];
        } else if (birth[a] < birth[b]) {
            b = parent[b];
        } else {
            a = parent[a];
            b = parent[b];
        }
    }
    return a;
}

int main() {
    init();
    
    int m;
    scanf("%d", &m);
    
    while (m--) {
        ll a, b;
        scanf("%lld %lld", &a, &b);
        printf("%lld\n", find_lca(a, b));
    }
    
    return 0;
}