#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define MAXN 500005
#define MAXM 500005
#define MAXT 100005

typedef long long ll;

struct Operation {
    int type;
    int x1, y1, x2, y2;
    ll c;
};

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

ll read() {
    ll n = 0;
    char c = getchar();
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') {
        n = n * 10 + c - '0';
        c = getchar();
    }
    return n;
}

void write(ll n) {
    if (n > 9) write(n / 10);
    putchar(n % 10 + '0');
}

ll a[MAXN][MAXM];
Operation operations[MAXT];

int main() {
    int n = read(), m = read(), x = read(), y = read(), t = read();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            a[i][j] = read();
        }
    }
    for (int i = 0; i < t; i++) {
        operations[i].type = read();
        operations[i].x1 = read();
        operations[i].y1 = read();
        operations[i].x2 = read();
        operations[i].y2 = read();
        if (operations[i].type == 1) {
            operations[i].c = read();
        }
    }

    for (int i = 0; i < t; i++) {
        if (operations[i].type == 0) {
            ll g = a[x][y];
            for (int j = x - operations[i].x1; j <= x + operations[i].x2; j++) {
                for (int k = y - operations[i].y1; k <= y + operations[i].y2; k++) {
                    g = gcd(g, a[j][k]);
                }
            }
            write(g);
            putchar('\n');
        } else {
            for (int j = operations[i].x1; j <= operations[i].x2; j++) {
                for (int k = operations[i].y1; k <= operations[i].y2; k++) {
                    a[j][k] += operations[i].c;
                }
            }
        }
    }

    return 0;
}