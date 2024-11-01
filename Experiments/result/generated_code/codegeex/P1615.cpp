#include <stdio.h>

int main() {
    int h1, m1, s1, h2, m2, s2, n;
    int total_seconds = 0;
    int stolen_notebooks = 0;

    // 读取输入时间
    scanf("%d:%d:%d", &h1, &m1, &s1);
    scanf("%d:%d:%d", &h2, &m2, &s2);
    // 读取每秒偷窃的笔记本数
    scanf("%d", &n);

    // 计算两个时间点之间的秒数差
    total_seconds += (h2 - h1) * 3600;
    total_seconds += (m2 - m1) * 60;
    total_seconds += (s2 - s1);

    // 计算猪八戒能偷到的笔记本总数
    stolen_notebooks = total_seconds * n;

    // 输出结果
    printf("%d\n", stolen_notebooks);

    return 0;
}