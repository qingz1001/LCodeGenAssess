#include <stdio.h>

int main() {
    int start_hour, start_minute, start_second;
    int end_hour, end_minute, end_second;
    int n;

    // 读取猪八戒开始偷的时间
    scanf("%d:%d:%d", &start_hour, &start_minute, &start_second);
    // 读取孙悟空开始偷的时间
    scanf("%d:%d:%d", &end_hour, &end_minute, &end_second);
    // 读取猪八戒每秒能偷的笔记本数
    scanf("%d", &n);

    // 将时间转换为秒
    int start_time = start_hour * 3600 + start_minute * 60 + start_second;
    int end_time = end_hour * 3600 + end_minute * 60 + end_second;

    // 计算猪八戒能偷的时间
    int total_time = end_time - start_time;

    // 计算猪八戒能偷的笔记本总数
    int total_notebooks = total_time * n;

    // 输出结果
    printf("%d\n", total_notebooks);

    return 0;
}