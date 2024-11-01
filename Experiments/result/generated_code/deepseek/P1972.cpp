#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000005

int n, m;
int a[MAXN];
int last[MAXN];
int cnt[MAXN];
int result[MAXN];

typedef struct {
    int l, r, idx;
} Query;

Query queries[MAXN];

int cmp(const void *a, const void *b) {
    Query *qa = (Query *)a;
    Query *qb = (Query *)b;
    if (qa->r != qb->r) return qa->r - qb->r;
    return qa->l - qb->l;
}

void solve() {
    int current_r = 0;
    int distinct_count = 0;

    for (int i = 0; i < m; i++) {
        while (current_r < queries[i].r) {
            current_r++;
            if (last[a[current_r]] != 0) {
                cnt[last[a[current_r]]]--;
                if (cnt[last[a[current_r]]] == 0) {
                    distinct_count--;
                }
            }
            last[a[current_r]] = current_r;
            cnt[current_r]++;
            if (cnt[current_r] == 1) {
                distinct_count++;
            }
        }

        while (current_r > queries[i].r) {
            cnt[current_r]--;
            if (cnt[current_r] == 0) {
                distinct_count--;
            }
            if (last[a[current_r]] == current_r) {
                last[a[current_r]] = 0;
            }
            current_r--;
        }

        while (current_r >= queries[i].l) {
            cnt[current_r]--;
            if (cnt[current_r] == 0) {
                distinct_count--;
            }
            if (last[a[current_r]] == current_r) {
                last[a[current_r]] = 0;
            }
            current_r--;
        }

        result[queries[i].idx] = distinct_count;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &queries[i].l, &queries[i].r);
        queries[i].idx = i;
    }

    qsort(queries, m, sizeof(Query), cmp);

    solve();

    for (int i = 0; i < m; i++) {
        printf("%d\n", result[i]);
    }

    return 0;
}