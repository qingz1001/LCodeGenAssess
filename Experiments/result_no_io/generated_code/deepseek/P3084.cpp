#include <stdio.h>
#include <stdlib.h>

#define MAXN 200000
#define MAXM 100000

int N, M;
int a[MAXM], b[MAXM];
int left[MAXN + 1], right[MAXN + 1];

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &a[i], &b[i]);
    }

    for (int i = 1; i <= N; i++) {
        left[i] = 0;
        right[i] = N + 1;
    }

    for (int i = 0; i < M; i++) {
        if (a[i] > 1) left[a[i] - 1] = a[i];
        right[b[i]] = b[i] + 1;
    }

    for (int i = N - 1; i >= 1; i--) {
        if (left[i] == 0) left[i] = left[i + 1];
    }

    for (int i = 2; i <= N; i++) {
        if (right[i] == N + 1) right[i] = right[i - 1];
    }

    int max_spotted = 0;
    int current_left = 1;

    for (int i = 1; i <= N; i++) {
        if (left[i] > right[i]) {
            printf("-1\n");
            return 0;
        }
        if (i == right[current_left]) {
            max_spotted++;
            current_left = i + 1;
        }
    }

    printf("%d\n", max_spotted);
    return 0;
}