#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_M 200

typedef long long ll;

ll b[MAX_N + 1];
int op[MAX_M + 1][3];

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

void swap(ll *a, ll *b) {
    ll temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", &b[i]);
    }

    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d", &op[i][0], &op[i][1], &op[i][2]);
    }

    for (int i = m; i >= 1; i--) {
        int type = op[i][0], x = op[i][1], y = op[i][2];
        if (type == 1) {
            b[x] -= b[y];
        } else {
            ll g = gcd(b[x], b[y]);
            if (b[x] % b[y] == 0) {
                b[x] /= b[y];
            } else {
                printf("No solution\n");
                return 0;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        printf("%lld ", b[i]);
    }
    printf("\n");

    return 0;
}