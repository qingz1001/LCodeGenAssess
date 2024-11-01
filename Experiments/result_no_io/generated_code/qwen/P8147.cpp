#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 100005
#define MAXL 500005

typedef struct {
    int id;
    int cnt;
} Item;

int cmp(const void *a, const void *b) {
    return ((Item *)b)->cnt - ((Item *)a)->cnt;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    char s[MAXN][MAXL];
    int v[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%s %d", s[i], &v[i]);
    }

    char S[MAXM][MAXL];
    int k[MAXM];
    for (int i = 0; i < m; i++) {
        scanf("%s %d", S[i], &k[i]);
    }

    for (int q = 0; q < m; q++) {
        int sum = 0;
        Item items[n];
        for (int i = 0; i < n; i++) {
            items[i].id = i;
            items[i].cnt = 0;
            char *pos = S[q];
            while ((pos = strstr(pos, s[i])) != NULL) {
                items[i].cnt++;
                pos += strlen(s[i]);
            }
            sum += items[i].cnt * v[i];
        }

        qsort(items, n, sizeof(Item), cmp);

        printf("%d\n", items[k[q] - 1].cnt * v[items[k[q] - 1].id]);
    }

    return 0;
}