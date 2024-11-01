#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_M 200

typedef long long ll;

ll b[MAX_N + 1];
ll a[MAX_N + 1];
int op[MAX_M + 1][3];

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

void swap(ll* a, ll* b) {
    ll temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", &b[i]);
        a[i] = b[i];
    }

    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d", &op[i][0], &op[i][1], &op[i][2]);
    }

    for (int i = m; i >= 1; i--) {
        int type = op[i][0], x = op[i][1], y = op[i][2];
        if (type == 1) {
            a[x] -= a[y];
        } else {
            ll g = gcd(a[x], a[y]);
            a[x] /= g;
            a[y] /= g;
            swap(&a[x], &a[y]);
        }
    }

    for (int i = 1; i <= n; i++) {
        printf("%lld ", a[i]);
    }

    return 0;
}