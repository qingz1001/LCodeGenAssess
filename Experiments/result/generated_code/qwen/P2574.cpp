#include <stdio.h>
#include <string.h>

#define MAXN 200005

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    char S[MAXN];
    scanf("%s", S);

    for (int i = 0; i < m; ++i) {
        int op, l, r;
        scanf("%d %d %d", &op, &l, &r);
        if (op == 0) {
            for (int j = l - 1; j < r; ++j) {
                if (S[j] == '0') {
                    S[j] = '1';
                } else {
                    S[j] = '0';
                }
            }
        } else if (op == 1) {
            int count = 0;
            for (int j = l - 1; j < r; ++j) {
                if (S[j] == '1') {
                    count++;
                }
            }
            printf("%d\n", count);
        }
    }

    return 0;
}