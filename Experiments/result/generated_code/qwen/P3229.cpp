#include <stdio.h>
#include <stdlib.h>

#define MAXN 500010
#define MAXM 200010

int n, m;
int a[MAXN];
int b[MAXN];
int x[MAXM];

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void solve() {
    int happy = 0, tired = 0;
    for (int i = 0; i < m; i++) {
        if (b[a[i]] == 1) {
            happy++;
        } else {
            tired++;
        }
        x[i] = a[i];
    }
    qsort(x, m, sizeof(int), compare);
    printf("%d", x[0]);
    for (int i = 1; i < m; i++) {
        printf(" %d", x[i]);
    }
    printf("\n");
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &a[i], &b[i]);
    }
    solve();
    return 0;
}