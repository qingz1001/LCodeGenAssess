#include <stdio.h>
#include <string.h>

#define MAXN 200005

int n, m;
char s[MAXN];

int main() {
    scanf("%d%d", &n, &m);
    scanf("%s", s + 1);

    while (m--) {
        int op, l, r;
        scanf("%d%d%d", &op, &l, &r);

        if (op == 0) {
            // 翻转区间 [l, r]
            for (int i = l; i <= r; i++) {
                s[i] = s[i] == '0' ? '1' : '0';
            }
        } else if (op == 1) {
            // 统计区间 [l, r] 内 '1' 的个数
            int count = 0;
            for (int i = l; i <= r; i++) {
                if (s[i] == '1') {
                    count++;
                }
            }
            printf("%d\n", count);
        }
    }

    return 0;
}