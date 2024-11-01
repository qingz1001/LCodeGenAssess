#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000005
#define MAXM 50005

int H, W, Q;
int R[MAXN], C[MAXN];
int A[MAXM], B[MAXM];
int id[MAXN], pos[MAXN];
int tree[MAXN];

void update(int x, int val) {
    while (x <= H * W) {
        tree[x] += val;
        x += x & -x;
    }
}

int query(int x) {
    int res = 0;
    while (x) {
        res += tree[x];
        x -= x & -x;
    }
    return res;
}

int get_id(int r, int c) {
    return r * W + c + 1;
}

long long calc() {
    long long res = 0;
    for (int r1 = 0; r1 < H; r1++) {
        for (int r2 = r1; r2 < H; r2++) {
            int cnt = 0, max_val = 0;
            memset(tree, 0, sizeof(tree));
            for (int c = 0; c < W; c++) {
                for (int r = r1; r <= r2; r++) {
                    int p = id[get_id(r, c)];
                    if (p < max_val) cnt++;
                    update(p + 1, 1);
                }
                while (cnt == query(max_val + 1)) {
                    res++;
                    max_val++;
                }
            }
        }
    }
    return res;
}

int main() {
    scanf("%d%d%d", &H, &W, &Q);
    for (int i = 0; i < H * W; i++) {
        scanf("%d%d", &R[i], &C[i]);
        pos[i] = get_id(R[i], C[i]);
        id[pos[i]] = i;
    }
    
    printf("%lld\n", calc());
    
    for (int i = 0; i < Q; i++) {
        scanf("%d%d", &A[i], &B[i]);
        int pa = pos[A[i]], pb = pos[B[i]];
        id[pa] = B[i];
        id[pb] = A[i];
        pos[A[i]] = pb;
        pos[B[i]] = pa;
        printf("%lld\n", calc());
    }
    
    return 0;
}