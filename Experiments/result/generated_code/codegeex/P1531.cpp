#include <stdio.h>
#include <string.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int scores[200005];

    // 初始化学生的成绩
    for (int i = 1; i <= n; i++) {
        scanf("%d", &scores[i]);
    }

    char operation[5];
    int a, b;

    // 处理操作
    for (int i = 0; i < m; i++) {
        scanf("%s %d %d", operation, &a, &b);
        if (operation[0] == 'Q') {
            // 查询操作
            int max = scores[a];
            for (int j = a + 1; j <= b; j++) {
                if (scores[j] > max) {
                    max = scores[j];
                }
            }
            printf("%d\n", max);
        } else if (operation[0] == 'U') {
            // 更新操作
            if (scores[a] < b) {
                scores[a] = b;
            }
        }
    }

    return 0;
}