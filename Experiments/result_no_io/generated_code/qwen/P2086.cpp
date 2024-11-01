#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 500005

int N, M;
int X, Y;
int T;
long long board[MAXN][MAXM];
long long prefix_sum[MAXN][MAXM];

void update(int x1, int y1, int x2, int y2, long long c) {
    for (int i = x1; i <= x2; ++i) {
        for (int j = y1; j <= y2; ++j) {
            board[i][j] += c;
        }
    }
}

long long query(int x1, int y1, int x2, int y2) {
    long long result = board[x1][y1];
    for (int i = x1 + 1; i <= x2; ++i) {
        result = __gcd(result, board[i][y1]);
    }
    for (int i = y1 + 1; i <= y2; ++i) {
        result = __gcd(result, board[x1][i]);
    }
    for (int i = x1 + 1; i <= x2; ++i) {
        for (int j = y1 + 1; j <= y2; ++j) {
            result = __gcd(result, board[i][j]);
        }
    }
    return result;
}

int main() {
    scanf("%d %d", &N, &M);
    scanf("%d %d", &X, &Y);
    scanf("%d", &T);

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            scanf("%lld", &board[i][j]);
        }
    }

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            prefix_sum[i][j] = board[i][j];
            if (i > 1) prefix_sum[i][j] += prefix_sum[i-1][j];
            if (j > 1) prefix_sum[i][j] += prefix_sum[i][j-1];
            if (i > 1 && j > 1) prefix_sum[i][j] -= prefix_sum[i-1][j-1];
        }
    }

    while (T--) {
        int op;
        scanf("%d", &op);
        if (op == 0) {
            int x1, y1, x2, y2;
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            printf("%lld\n", query(X + x1, Y + y1, X + x2, Y + y2));
        } else {
            int x1, y1, x2, y2;
            long long c;
            scanf("%d %d %d %d %lld", &x1, &y1, &x2, &y2, &c);
            update(X + x1, Y + y1, X + x2, Y + y2, c);
        }
    }

    return 0;
}