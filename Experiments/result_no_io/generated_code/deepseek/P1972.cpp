#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000005

int n, m;
int a[MAXN];
int cnt[MAXN];
int result[MAXN];

typedef struct {
    int l, r, idx;
} Query;

Query queries[MAXN];

int cmp(const void *a, const void *b) {
    Query *qa = (Query *)a;
    Query *qb = (Query *)b;
    if (qa->l / 1000 != qb->l / 1000) return qa->l / 1000 - qb->l / 1000;
    return qa->r - qb->r;
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

    int currentL = 0, currentR = 0;
    int currentAnswer = 0;

    for (int i = 0; i < m; i++) {
        int l = queries[i].l, r = queries[i].r;

        while (currentR <= r) {
            if (cnt[a[currentR]] == 0) currentAnswer++;
            cnt[a[currentR]]++;
            currentR++;
        }
        while (currentR > r + 1) {
            currentR--;
            cnt[a[currentR]]--;
            if (cnt[a[currentR]] == 0) currentAnswer--;
        }
        while (currentL < l) {
            cnt[a[currentL]]--;
            if (cnt[a[currentL]] == 0) currentAnswer--;
            currentL++;
        }
        while (currentL > l) {
            currentL--;
            if (cnt[a[currentL]] == 0) currentAnswer++;
            cnt[a[currentL]]++;
        }

        result[queries[i].idx] = currentAnswer;
    }

    for (int i = 0; i < m; i++) {
        printf("%d\n", result[i]);
    }

    return 0;
}