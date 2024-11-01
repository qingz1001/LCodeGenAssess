#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 100005

int N, M, X, Y, T;
long long board[MAXN][MAXM];
long long gcd(long long a, long long b) {
    return b ? gcd(b, a % b) : a;
}

void update(int x1, int y1, int x2, int y2, int c) {
    for (int i = x1; i <= x2; ++i) {
        for (int j = y1; j <= y2; ++j) {
            board[i][j] += c;
        }
    }
}

long long query(int x1, int y1, int x2, int y2) {
    long long result = board[x1][y1];
    for (int i = x1; i <= x2; ++i) {
        for (int j = y1; j <= y2; ++j) {
            result = gcd(result, board[i][j]);
        }
    }
    return result;
}

int main() {
    scanf("%d%d", &N, &M);
    scanf("%d%d", &X, &Y);
    scanf("%d", &T);

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            scanf("%lld", &board[i][j]);
        }
    }

    while (T--) {
        int type;
        scanf("%d", &type);
        if (type == 0) {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            printf("%lld\n", query(X + x1, Y + y1, X + x2, Y + y2));
        } else if (type == 1) {
            int x1, y1, x2, y2, c;
            scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &c);
            update(x1 + X, y1 + Y, x2 + X, y2 + Y, c);
        }
    }

    return 0;
}