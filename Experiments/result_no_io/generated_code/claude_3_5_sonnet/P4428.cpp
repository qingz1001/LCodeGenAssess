#include <stdio.h>
#include <string.h>
#define MAXN 100005
#define MOD 3

int n, m;
char s[MAXN];
int prefix_sum[MAXN][3];

void update_prefix_sum(int pos) {
    int val = s[pos] - '0';
    for (int i = pos; i <= n; i++) {
        for (int j = 0; j < 3; j++) {
            prefix_sum[i][j] = prefix_sum[i-1][j];
        }
        prefix_sum[i][(i-pos+1) % 3] += val;
        prefix_sum[i][(i-pos+1) % 3] %= MOD;
    }
}

int query(int l, int r) {
    int count = 0;
    for (int len = 1; len <= r-l+1; len++) {
        int sum[3] = {0};
        for (int j = 0; j < 3; j++) {
            sum[j] = (prefix_sum[r][j] - prefix_sum[l-1][j] + MOD) % MOD;
        }
        if ((sum[0] + sum[1] + sum[2]) % MOD == 0) {
            count++;
        }
    }
    return count;
}

int main() {
    scanf("%d", &n);
    scanf("%s", s+1);

    memset(prefix_sum, 0, sizeof(prefix_sum));
    for (int i = 1; i <= n; i++) {
        update_prefix_sum(i);
    }

    scanf("%d", &m);
    while (m--) {
        int op, x, y;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d", &x);
            s[x] = (s[x] == '0') ? '1' : '0';
            update_prefix_sum(x);
        } else {
            scanf("%d %d", &x, &y);
            printf("%d\n", query(x, y));
        }
    }

    return 0;
}