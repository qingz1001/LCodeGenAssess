#include <stdio.h>
#include <string.h>

#define MAX_PLACES 20
#define MAX_NAME_LENGTH 100
#define MAX_DAYS 1000000

char convenient_places[MAX_PLACES][MAX_NAME_LENGTH];
char daily_schedule[MAX_DAYS][MAX_NAME_LENGTH];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    getchar(); // 消耗换行符

    // 读取方便去的地方
    for (int i = 0; i < n; i++) {
        fgets(convenient_places[i], MAX_NAME_LENGTH, stdin);
        convenient_places[i][strcspn(convenient_places[i], "\n")] = 0; // 去除换行符
    }

    // 读取日程表
    for (int i = 0; i < m; i++) {
        fgets(daily_schedule[i], MAX_NAME_LENGTH, stdin);
        daily_schedule[i][strcspn(daily_schedule[i], "\n")] = 0; // 去除换行符
    }

    int count = 0;
    // 统计在同一地方的天数
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (strcmp(daily_schedule[i], convenient_places[j]) == 0) {
                count++;
                break;
            }
        }
    }

    printf("%d\n", count);

    return 0;
}