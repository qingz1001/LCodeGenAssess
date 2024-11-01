#include <stdio.h>

#define MAXN 100001

int n, w;
int seq[MAXN];

int main() {
    char op;
    int a, b;
    
    // 读取序列长度和操作次数
    scanf("%d %d", &n, &w);
    
    // 初始化序列
    for (int i = 1; i <= n; i++) {
        seq[i] = 0;
    }
    
    // 处理每次操作
    for (int i = 0; i < w; i++) {
        scanf(" %c %d %d", &op, &a, &b);
        
        if (op == 'x') {
            // 加法操作
            seq[a] += b;
        } else if (op == 'y') {
            // 查询操作，计算区间和
            int sum = 0;
            for (int j = a; j <= b; j++) {
                sum += seq[j];
            }
            printf("%d\n", sum);
        }
    }
    
    return 0;
}