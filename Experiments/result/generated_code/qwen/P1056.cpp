#include <stdio.h>
#include <stdlib.h>

#define MAX_M 1000
#define MAX_N 1000
#define MAX_D 2000

int M, N, K, L, D;
int pairs[MAX_D][4];
int rows[MAX_M + 1], cols[MAX_N + 1];

void read_input() {
    scanf("%d %d %d %d %d", &M, &N, &K, &L, &D);
    for (int i = 0; i < D; ++i) {
        scanf("%d %d %d %d", &pairs[i][0], &pairs[i][1], &pairs[i][2], &pairs[i][3]);
    }
}

void find_channels() {
    for (int i = 0; i < D; ++i) {
        int x1 = pairs[i][0], y1 = pairs[i][1], x2 = pairs[i][2], y2 = pairs[i][3];
        if (x1 == x2) {
            if (y1 > y2) {
                y1 ^= y2, y2 ^= y1, y1 ^= y2;
            }
            cols[y1 + 1] = 1;
        } else {
            if (x1 > x2) {
                x1 ^= x2, x2 ^= x1, x1 ^= x2;
            }
            rows[x1 + 1] = 1;
        }
    }
}

void print_output() {
    int count = 0;
    printf("%d\n", K);
    for (int i = 1; i <= M; ++i) {
        if (rows[i]) {
            printf("%d ", i);
            ++count;
        }
    }
    printf("\n%d\n", L);
    for (int j = 1; j <= N; ++j) {
        if (cols[j]) {
            printf("%d ", j);
            ++count;
        }
    }
    printf("\n");
}

int main() {
    read_input();
    find_channels();
    print_output();
    return 0;
}