#include <stdio.h>
#include <stdlib.h>

#define MAXN 10000
#define MAXM 1000

int a[MAXN];
int dp[MAXN];
int pre[MAXN];
int lis[MAXN];

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

void find_lis(int n) {
    int len = 0;
    int *d = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 0; i < n; i++) {
        int pos = qsearch(d, len, a[i]);
        d[pos] = a[i];
        dp[i] = pos + 1;
        if (pos == len) len++;
    }
    free(d);
}

int qsearch(int *d, int len, int key) {
    int l = 0, r = len - 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (d[mid] < key) l = mid + 1;
        else r = mid - 1;
    }
    return l;
}

void print_lis(int n, int l) {
    int len = 0;
    for (int i = 0; i < n; i++) {
        if (dp[i] >= l) {
            lis[len++] = a[i];
            l--;
            if (l == 0) break;
        }
    }
    if (l > 0) {
        printf("Impossible\n");
    } else {
        for (int i = 0; i < len; i++) {
            printf("%d ", lis[i]);
        }
        printf("\n");
    }
}

int main() {
    int n, m;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    find_lis(n);
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int l;
        scanf("%d", &l);
        print_lis(n, l);
    }
    return 0;
}