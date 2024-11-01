#include <stdio.h>

int n, opt, mod, min, max, final;
int a[1000005];

int main() {
    // 读取输入
    scanf("%d %d %d %d %d", &n, &opt, &mod, &min, &max);
    
    // 处理前opt个操作
    for (int i = 0; i < opt; i++) {
        char op;
        int l, r, x;
        scanf(" %c %d %d %d", &op, &l, &r, &x);
        if (op == 'A') {
            // 区间加操作
            for (int j = l; j <= r; j++) {
                a[j] += x;
            }
        } else if (op == 'Q') {
            // 区间查询操作
            int count = 0;
            for (int j = l; j <= r; j++) {
                if (min <= (a[j] * j) % mod && (a[j] * j) % mod <= max) {
                    count++;
                }
            }
            printf("%d\n", count);
        }
    }
    
    // 读取final值
    scanf("%d", &final);
    
    // 处理final个询问操作
    for (int i = 0; i < final; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        int count = 0;
        for (int j = l; j <= r; j++) {
            if (min <= (a[j] * j) % mod && (a[j] * j) % mod <= max) {
                count++;
            }
        }
        printf("%d\n", count);
    }
    
    return 0;
}