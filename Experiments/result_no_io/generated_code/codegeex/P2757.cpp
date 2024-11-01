#include <stdio.h>
#include <string.h>

#define MAXN 500005

int T, N, A[MAXN];
int st[MAXN][20], Log[MAXN];

void buildST() {
    for (int i = 1; i <= N; i++) st[i][0] = A[i];
    for (int j = 1; (1 << j) <= N; j++) {
        for (int i = 1; i + (1 << j) - 1 <= N; i++) {
            st[i][j] = st[i][j - 1] < st[i + (1 << (j - 1))][j - 1] ? st[i][j - 1] : st[i + (1 << (j - 1))][j - 1];
        }
    }
}

int query(int l, int r) {
    int k = Log[r - l + 1];
    return st[l][k] < st[r - (1 << k) + 1][k] ? st[l][k] : st[r - (1 << k) + 1][k];
}

int main() {
    scanf("%d", &T);
    for (int i = 2; i < MAXN; i++) Log[i] = Log[i / 2] + 1;
    while (T--) {
        scanf("%d", &N);
        for (int i = 1; i <= N; i++) scanf("%d", &A[i]);
        buildST();
        int flag = 0;
        for (int i = 1; i <= N; i++) {
            for (int j = i + 2; j <= N; j += 2) {
                int k = (j - i) / 2;
                int l = i + k, r = j - k;
                if (query(l, r) != A[i]) {
                    flag = 1;
                    break;
                }
            }
            if (flag) break;
        }
        if (flag) printf("Y\n");
        else printf("N\n");
    }
    return 0;
}