#include <stdio.h>

typedef struct {
    int students;
    int distance;
    char name[100];
} City;

int main() {
    City cities[150];
    int numCities = 0;
    int minCost = 0;
    int minIndex = 0;

    // 读取输入数据
    while (scanf("%d %d %s", &cities[numCities].students, &cities[numCities].distance, cities[numCities].name) != EOF) {
        numCities++;
    }

    // 计算最小花费
    for (int i = 0; i < numCities; i++) {
        int cost = 0;
        for (int j = 0; j < numCities; j++) {
            cost += (cities[i].distance - cities[j].distance) * cities[j].students;
        }
        if (i == 0 || cost < minCost) {
            minCost = cost;
            minIndex = i;
        }
    }

    // 输出结果
    printf("%s %d\n", cities[minIndex].name, minCost);

    return 0;
}