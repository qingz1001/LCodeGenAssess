#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n, m;
int binary[MAXN];

int is_multiple_of_3(int l, int r) {
    int count_1 = 0;
    for (int i = l; i <= r; i++) {
        if (binary[i] == 1) {
            count_1++;
        }
    }
    return count_1 % 3 == 0;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &binary[i]);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int type, l, r;
        scanf("%d", &type);
        if (type == 1) {
            scanf("%d", &l);
            binary[l] = 1 - binary[l];
        } else if (type == 2) {
            scanf("%d %d", &l, &r);
            int count = 0;
            for (int j = l; j <= r; j++) {
                for (int k = j; k <= r; k++) {
                    if (is_multiple_of_3(j, k)) {
                        count++;
                    }
                }
            }
            printf("%d\n", count);
        }
    }
    return 0;
}