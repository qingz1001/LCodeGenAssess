#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAXN 500005
#define MAXM 500005

typedef int64_t ll;

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

ll board[MAXN][MAXM];
ll diff[MAXN][MAXM];
ll gcd_diff[MAXN][MAXM];

int N, M, X, Y, T;

void update_diff(int x1, int y1, int x2, int y2, ll c) {
    diff[x1][y1] += c;
    if (x2 + 1 <= N) diff[x2 + 1][y1] -= c;
    if (y2 + 1 <= M) diff[x1][y2 + 1] -= c;
    if (x2 + 1 <= N && y2 + 1 <= M) diff[x2 + 1][y2 + 1] += c;
}

void apply_diff() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
            board[i][j] += diff[i][j];
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            diff[i][j] = 0;
        }
    }
}

ll query_gcd(int x1, int y1, int x2, int y2) {
    ll result = board[x1][y1];
    for (int i = x1; i <= x2; i++) {
        for (int j = y1; j <= y2; j++) {
            result = gcd(result, board[i][j]);
        }
    }
    return result;
}

int main() {
    scanf("%d %d", &N, &M);
    scanf("%d %d", &X, &Y);
    scanf("%d", &T);

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            scanf("%lld", &board[i][j]);
        }
    }

    for (int t = 0; t < T; t++) {
        int op;
        scanf("%d", &op);
        if (op == 0) {
            int x1, y1, x2, y2;
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            x1 = X - x1;
            x2 = X + x2;
            y1 = Y - y1;
            y2 = Y + y2;
            if (x1 < 1) x1 = 1;
            if (x2 > N) x2 = N;
            if (y1 < 1) y1 = 1;
            if (y2 > M) y2 = M;
            printf("%lld\n", query_gcd(x1, y1, x2, y2));
        } else if (op == 1) {
            int x1, y1, x2, y2;
            ll c;
            scanf("%d %d %d %d %lld", &x1, &y1, &x2, &y2, &c);
            update_diff(x1, y1, x2, y2, c);
        }
    }

    apply_diff();

    return 0;
}