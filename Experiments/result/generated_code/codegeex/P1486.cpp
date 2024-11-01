#include <stdio.h>
#include <stdlib.h>

#define MAXN 300005

int n, min;
char op;
int k;
int cnt = 0;
int tree[MAXN * 4];
int salary[MAXN];
int leave[MAXN];

void build(int l, int r, int pos) {
    if (l == r) {
        tree[pos] = 0;
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, pos * 2);
    build(mid + 1, r, pos * 2 + 1);
    tree[pos] = tree[pos * 2] + tree[pos * 2 + 1];
}

void update(int l, int r, int pos, int x, int val) {
    if (l == r) {
        tree[pos] += val;
        return;
    }
    int mid = (l + r) / 2;
    if (x <= mid) {
        update(l, mid, pos * 2, x, val);
    } else {
        update(mid + 1, r, pos * 2 + 1, x, val);
    }
    tree[pos] = tree[pos * 2] + tree[pos * 2 + 1];
}

int query(int l, int r, int pos, int k) {
    if (l == r) {
        return l;
    }
    int mid = (l + r) / 2;
    if (tree[pos * 2] >= k) {
        return query(l, mid, pos * 2, k);
    } else {
        return query(mid + 1, r, pos * 2 + 1, k - tree[pos * 2]);
    }
}

int main() {
    scanf("%d %d", &n, &min);
    build(1, MAXN, 1);

    for (int i = 0; i < n; i++) {
        scanf(" %c %d", &op, &k);
        if (op == 'I') {
            if (k < min) {
                leave[cnt++] = k;
            } else {
                salary[cnt++] = k;
                update(1, MAXN, 1, k, 1);
            }
        } else if (op == 'A') {
            for (int j = 0; j < cnt; j++) {
                salary[j] += k;
                if (salary[j] < min) {
                    leave[cnt++] = salary[j];
                    update(1, MAXN, 1, salary[j], -1);
                    salary[j] = 0;
                }
            }
        } else if (op == 'S') {
            for (int j = 0; j < cnt; j++) {
                salary[j] -= k;
                if (salary[j] < min) {
                    leave[cnt++] = salary[j];
                    update(1, MAXN, 1, salary[j], -1);
                    salary[j] = 0;
                }
            }
        } else if (op == 'F') {
            if (tree[1] < k) {
                printf("-1\n");
            } else {
                int index = query(1, MAXN, 1, k);
                int left = 1, right = MAXN, mid;
                while (left < right) {
                    mid = (left + right) / 2;
                    if (query(1, MAXN, 1, mid) >= k) {
                        right = mid;
                    } else {
                        left = mid + 1;
                    }
                }
                printf("%d\n", left);
            }
        }
    }
    printf("%d\n", cnt);
    return 0;
}