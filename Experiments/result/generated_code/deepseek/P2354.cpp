#include <stdio.h>
#include <stdlib.h>

#define MAXN 5000
#define MAXM 5000

typedef long long ll;

ll x0, a, b, c, d;
int N, M, Q;
int T[MAXN * MAXM + 1];
int board[MAXN + 1][MAXM + 1];
int path[MAXN + M];

ll next_random() {
    x0 = (a * x0 * x0 + b * x0 + c) % d;
    return x0;
}

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void generate_random_permutation() {
    for (int i = 1; i <= N * M; i++) {
        T[i] = i;
    }
    for (int i = 1; i <= N * M; i++) {
        int j = (next_random() % i) + 1;
        swap(&T[i], &T[j]);
    }
    for (int i = 0; i < Q; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        swap(&T[u], &T[v]);
    }
}

void fill_board() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            board[i][j] = T[(i - 1) * M + j];
        }
    }
}

void find_min_path() {
    int path_index = 0;
    int i = 1, j = 1;
    path[path_index++] = board[i][j];
    while (i < N || j < M) {
        if (i == N) {
            j++;
        } else if (j == M) {
            i++;
        } else {
            if (board[i + 1][j] < board[i][j + 1]) {
                i++;
            } else {
                j++;
            }
        }
        path[path_index++] = board[i][j];
    }
}

int main() {
    scanf("%lld %lld %lld %lld %lld", &x0, &a, &b, &c, &d);
    scanf("%d %d %d", &N, &M, &Q);

    generate_random_permutation();
    fill_board();
    find_min_path();

    for (int i = 0; i < N + M - 1; i++) {
        printf("%d ", path[i]);
    }
    printf("\n");

    return 0;
}