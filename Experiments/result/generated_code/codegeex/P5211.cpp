#include <stdio.h>

int n, q;
int s[200005];

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &s[i]);
    }

    for (int i = 0; i < q; i++) {
        int op, l, r;
        scanf("%d %d %d", &op, &l, &r);

        if (op == 1) {
            int d;
            scanf("%d", &d);
            for (int j = l; j <= r; j++) {
                s[j] += d;
            }
        } else if (op == 2) {
            int min_pos = l;
            for (int j = r; j >= l; j--) {
                if (s[j] < s[min_pos]) {
                    min_pos = j;
                }
            }
            printf("%d\n", min_pos);
        }
    }

    return 0;
}