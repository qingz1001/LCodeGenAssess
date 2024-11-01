#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    char names[101][21];
    int count[101] = {0}; // 存储每个孩子取的食物份数
    int total = 0; // 存储其他人取的食物份数总和
    int reminders = 0; // 存储妈妈提醒的次数

    for (int i = 0; i < n; i++) {
        scanf("%s", names[i]);
        count[i]++;
        for (int j = 0; j < i; j++) {
            if (strcmp(names[i], names[j]) != 0) {
                total += count[j];
            }
        }
        if (count[i] > total) {
            reminders++;
        }
    }

    printf("%d\n", reminders);
    return 0;
}