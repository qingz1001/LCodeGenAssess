#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef struct {
    int l, r, K, D;
} Update;

int n, m;
int a[MAXN];
Update updates[MAXN];

void apply_update(int pos, int val) {
    a[pos] += val;
}

void process_updates() {
    for (int i = 0; i < m; i++) {
        if (updates[i].l == 0 && updates[i].r == 0) {
            continue; // Skip placeholder update
        }
        int l = updates[i].l, r = updates[i].r, K = updates[i].K, D = updates[i].D;
        for (int j = l; j <= r; j++) {
            apply_update(j, K + (j - l) * D);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    // Initialize with placeholders to avoid index issues
    for (int i = 0; i < m; i++) {
        updates[i].l = 0;
        updates[i].r = 0;
        updates[i].K = 0;
        updates[i].D = 0;
    }

    for (int i = 0; i < m; i++) {
        int opt;
        scanf("%d", &opt);
        if (opt == 1) {
            int l, r, K, D;
            scanf("%d %d %d %d", &l, &r, &K, &D);
            updates[l-1].l = l;
            updates[l-1].r = r;
            updates[l-1].K = K;
            updates[l-1].D = D;
        } else if (opt == 2) {
            int p;
            scanf("%d", &p);
            printf("%d\n", a[p]);
        }
    }

    process_updates();

    return 0;
}