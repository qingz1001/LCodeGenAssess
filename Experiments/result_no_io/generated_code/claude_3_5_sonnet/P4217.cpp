#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define INF 0x3f3f3f3f3f3f3f3fLL

typedef long long ll;

int N;
int D[MAXN], U[MAXN], P[MAXN], M[MAXN], C[MAXN];
ll f[MAXN], g[MAXN];

ll min(ll a, ll b) {
    return a < b ? a : b;
}

int main() {
    freopen("product.in", "r", stdin);
    freopen("product.out", "w", stdout);

    scanf("%d", &N);
    for(int i = 1; i <= N; i++) scanf("%d", &D[i]);
    for(int i = 1; i <= N; i++) scanf("%d", &U[i]);
    for(int i = 1; i <= N; i++) scanf("%d", &P[i]);
    for(int i = 1; i < N; i++) scanf("%d", &M[i]);
    for(int i = 1; i < N; i++) scanf("%d", &C[i]);

    memset(f, 0x3f, sizeof(f));
    memset(g, 0x3f, sizeof(g));
    f[0] = g[0] = 0;

    for(int i = 1; i <= N; i++) {
        ll sum = 0;
        for(int j = i; j >= 1; j--) {
            sum += D[j];
            if(sum > U[i]) break;
            ll cost = (ll)P[i] * sum;
            for(int k = j; k < i; k++) {
                cost += (ll)C[k] * (sum - D[j]);
            }
            f[i] = min(f[i], g[j-1] + cost);
        }
        if(i < N) {
            for(int j = 0; j <= U[i]; j++) {
                g[i] = min(g[i], f[i] + (ll)M[i] * j);
            }
        }
    }

    printf("%lld\n", f[N]);

    return 0;
}