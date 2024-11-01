#include <stdio.h>
#include <string.h>
#define MAXN 100005

int n, m;
int a[MAXN];
int sum[MAXN][3];
int cnt[3];

void update(int pos) {
    a[pos] ^= 1;
    for (int i = pos; i <= n; i++) {
        sum[i][0] = sum[i-1][0];
        sum[i][1] = sum[i-1][1];
        sum[i][2] = sum[i-1][2];
        sum[i][a[i]]++;
    }
}

int query(int l, int r) {
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < 3; i++) {
        cnt[i] = sum[r][i] - sum[l-1][i];
    }
    
    int total = r - l + 1;
    int result = 0;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) continue;
            int k = 3 - i - j;
            if (cnt[i] > 0 && cnt[j] > 0 && cnt[k] > 0) {
                result += (total - 2) * (total - 1) / 2;
            } else if ((cnt[i] > 0 && cnt[j] > 0) || (cnt[i] > 0 && cnt[k] > 0) || (cnt[j] > 0 && cnt[k] > 0)) {
                result += total - 1;
            }
        }
    }
    
    if (cnt[0] > 0) result++;
    
    return result;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        sum[i][0] = sum[i-1][0];
        sum[i][1] = sum[i-1][1];
        sum[i][2] = sum[i-1][2];
        sum[i][a[i]]++;
    }
    
    scanf("%d", &m);
    while (m--) {
        int op, x, y;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d", &x);
            update(x);
        } else {
            scanf("%d%d", &x, &y);
            printf("%d\n", query(x, y));
        }
    }
    
    return 0;
}