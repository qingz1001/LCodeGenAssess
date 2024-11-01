#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int N, M;
int lights[MAXN];
int diff[MAXN];

void update(int l, int r) {
    diff[l] ^= 1;
    if (r + 1 < N) diff[r + 1] ^= 1;
}

int query(int l, int r) {
    int count = 0;
    int state = 0;
    for (int i = 0; i < l; i++) state ^= diff[i];
    for (int i = l; i <= r; i++) {
        state ^= diff[i];
        if (state) count++;
    }
    return count;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < M; i++) {
        int op, S, E;
        scanf("%d %d %d", &op, &S, &E);
        if (op == 0) {
            update(S - 1, E - 1);
        } else if (op == 1) {
            printf("%d\n", query(S - 1, E - 1));
        }
    }
    return 0;
}