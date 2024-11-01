#include <stdio.h>
#include <string.h>

#define MAX_N 200005

int tree[MAX_N];
char s[MAX_N];
int n, m;

void update(int x, int val) {
    while (x <= n) {
        tree[x] += val;
        x += x & -x;
    }
}

int query(int x) {
    int sum = 0;
    while (x > 0) {
        sum += tree[x];
        x -= x & -x;
    }
    return sum;
}

int main() {
    scanf("%d %d", &n, &m);
    scanf("%s", s + 1);

    for (int i = 1; i <= n; i++) {
        if (s[i] == '1') {
            update(i, 1);
        }
    }

    for (int i = 0; i < m; i++) {
        int op, l, r;
        scanf("%d %d %d", &op, &l, &r);

        if (op == 0) {
            for (int j = l; j <= r; j++) {
                if (s[j] == '0') {
                    s[j] = '1';
                    update(j, 1);
                } else {
                    s[j] = '0';
                    update(j, -1);
                }
            }
        } else {
            printf("%d\n", query(r) - query(l - 1));
        }
    }

    return 0;
}