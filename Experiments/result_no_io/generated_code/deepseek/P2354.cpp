#include <stdio.h>
#include <stdlib.h>

#define MAXN 5000
#define MAXM 5000

typedef long long ll;

ll x0, a, b, c, d;
int N, M, Q;
int T[MAXN * MAXM + 1];
int board[MAXN + 1][MAXM + 1];
int visited[MAXN + 1][MAXM + 1];

ll next_random() {
    ll x = x0;
    x = (a * x * x + b * x + c) % d;
    x0 = x;
    return x;
}

void swap(int *arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void generate_random_permutation() {
    for (int i = 1; i <= N * M; i++) {
        T[i] = i;
    }
    for (int i = 1; i <= N * M; i++) {
        ll xi = next_random();
        int j = (xi % i) + 1;
        swap(T, i, j);
    }
    for (int i = 0; i < Q; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        swap(T, u, v);
    }
}

void fill_board() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            board[i][j] = T[(i - 1) * M + j];
        }
    }
}

void find_min_path(int x, int y, int *path, int *path_index) {
    if (x > N || y > M || visited[x][y]) return;
    visited[x][y] = 1;
    path[(*path_index)++] = board[x][y];
    if (x == N && y == M) return;
    if (x < N && y < M) {
        if (board[x + 1][y] < board[x][y + 1]) {
            find_min_path(x + 1, y, path, path_index);
        } else {
            find_min_path(x, y + 1, path, path_index);
        }
    } else if (x < N) {
        find_min_path(x + 1, y, path, path_index);
    } else {
        find_min_path(x, y + 1, path, path_index);
    }
}

int main() {
    scanf("%lld %lld %lld %lld %lld", &x0, &a, &b, &c, &d);
    scanf("%d %d %d", &N, &M, &Q);

    generate_random_permutation();
    fill_board();

    int path[N + M - 1];
    int path_index = 0;
    find_min_path(1, 1, path, &path_index);

    for (int i = 0; i < N + M - 1; i++) {
        printf("%d ", path[i]);
    }
    printf("\n");

    return 0;
}