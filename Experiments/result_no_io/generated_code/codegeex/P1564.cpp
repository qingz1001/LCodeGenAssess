#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int students[2501];
    for (int i = 0; i < n; i++) {
        scanf("%d", &students[i]);
    }

    int min_rooms = n; // 初始化最小机房数为n，即每个学生一个机房
    for (int i = 0; i < n; i++) {
        int count[3] = {0}; // count[1]记录崇拜神牛甲的人数，count[2]记录崇拜神牛乙的人数
        for (int j = i; j < n; j++) {
            count[students[j]]++;
            int max_students = (count[1] > count[2]) ? count[1] : count[2];
            int min_students = (count[1] < count[2]) ? count[1] : count[2];
            if (max_students - min_students <= m) {
                min_rooms = (min_rooms < (j - i + 1)) ? min_rooms : (j - i + 1);
            }
        }
    }

    printf("%d\n", min_rooms);
    return 0;
}