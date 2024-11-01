#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int N, M;
int lights[MAXN];
int diff[MAXN];

void toggle(int l, int r) {
    diff[l] ^= 1;
    if (r + 1 < N) diff[r + 1] ^= 1;
}

int query(int l, int r) {
    int sum = 0;
    for (int i = 0; i < N; i++) {
        if (i > 0) diff[i] ^= diff[i - 1];
        lights[i] ^= diff[i];
        if (i >= l && i <= r && lights[i]) sum++;
    }
    return sum;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < M; i++) {
        int op, l, r;
        scanf("%d %d %d", &op, &l, &r);
        if (op == 0) {
            toggle(l - 1, r - 1);
        } else {
            printf("%d\n", query(l - 1, r - 1));
        }
    }
    return 0;
}