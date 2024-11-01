#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000005

int H, W, Q;
int R[MAXN], C[MAXN];
int A[MAXN], B[MAXN];
int seat[MAXN], pos[MAXN];
int left[MAXN], right[MAXN], up[MAXN], down[MAXN];

int get(int x) {
    return x == pos[x] ? x : (pos[x] = get(pos[x]));
}

void merge(int x, int y) {
    x = get(x);
    y = get(y);
    if (x != y) {
        pos[x] = y;
        left[y] = left[x] < left[y] ? left[x] : left[y];
        right[y] = right[x] > right[y] ? right[x] : right[y];
        up[y] = up[x] < up[y] ? up[x] : up[y];
        down[y] = down[x] > down[y] ? down[x] : down[y];
    }
}

int main() {
    scanf("%d%d%d", &H, &W, &Q);
    for (int i = 0; i < H * W; i++) {
        scanf("%d%d", &R[i], &C[i]);
        seat[i] = R[i] * W + C[i];
        pos[i] = i;
        left[i] = right[i] = C[i];
        up[i] = down[i] = R[i];
    }

    for (int i = 0; i < Q; i++) {
        scanf("%d%d", &A[i], &B[i]);
    }

    int ans = 0;
    for (int i = 0; i < H * W; i++) {
        int r = R[i], c = C[i];
        if (r > 0 && seat[get(i - W)] == seat[i] - W) merge(i, i - W);
        if (c > 0 && seat[get(i - 1)] == seat[i] - 1) merge(i, i - 1);
        int root = get(i);
        if (left[root] == 0 && right[root] == c && up[root] == 0 && down[root] == r)
            ans++;
    }

    printf("%d\n", ans);

    for (int i = 0; i < Q - 1; i++) {
        int a = A[i], b = B[i];
        int sa = seat[a], sb = seat[b];
        seat[a] = sb;
        seat[b] = sa;

        for (int j = 0; j < H * W; j++) pos[j] = j;
        for (int j = 0; j < H * W; j++) {
            left[j] = right[j] = C[j];
            up[j] = down[j] = R[j];
        }

        ans = 0;
        for (int j = 0; j < H * W; j++) {
            int r = R[j], c = C[j];
            if (r > 0 && seat[get(j - W)] == seat[j] - W) merge(j, j - W);
            if (c > 0 && seat[get(j - 1)] == seat[j] - 1) merge(j, j - 1);
            int root = get(j);
            if (left[root] == 0 && right[root] == c && up[root] == 0 && down[root] == r)
                ans++;
        }

        printf("%d\n", ans);
    }

    return 0;
}