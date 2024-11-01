#include <stdio.h>

int main() {
    int start_hour, start_minute, start_second;
    int end_hour, end_minute, end_second;
    int n;

    // 读取猪八戒开始偷笔记本的时间
    scanf("%d:%d:%d", &start_hour, &start_minute, &start_second);

    // 读取孙悟空开始偷平底锅的时间
    scanf("%d:%d:%d", &end_hour, &end_minute, &end_second);

    // 读取猪八戒每秒能偷的笔记本数
    scanf("%d", &n);

    // 计算时间差（秒）
    int start_time_in_seconds = start_hour * 3600 + start_minute * 60 + start_second;
    int end_time_in_seconds = end_hour * 3600 + end_minute * 60 + end_second;
    int time_difference = end_time_in_seconds - start_time_in_seconds;

    // 计算猪八戒能偷的笔记本总数
    int total_notebooks = time_difference * n;

    // 输出结果
    printf("%d\n", total_notebooks);

    return 0;
}