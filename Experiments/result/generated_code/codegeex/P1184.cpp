#include <stdio.h>
#include <string.h>

#define MAX_N 20
#define MAX_M 1000000

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    char convenientPlaces[MAX_N][51]; // 保存高手方便去的地点
    char herPlace[MAX_M][51]; // 保存她每天所在的地点

    // 读取高手方便去的地点
    for (int i = 0; i < n; i++) {
        scanf("%s", convenientPlaces[i]);
    }

    // 读取她每天所在的地点
    for (int i = 0; i < m; i++) {
        scanf("%s", herPlace[i]);
    }

    int count = 0; // 记录他们在同一个地方的天数

    // 遍历她每天所在的地点，检查是否在高手方便去的地点中
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (strcmp(herPlace[i], convenientPlaces[j]) == 0) {
                count++;
                break; // 找到匹配的地点，跳出内层循环
            }
        }
    }

    printf("%d\n", count);

    return 0;
}