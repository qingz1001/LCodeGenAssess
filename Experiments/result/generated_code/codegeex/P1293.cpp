#include <stdio.h>
#include <string.h>

typedef struct {
    int students;
    int distance;
    char name[100];
} City;

int main() {
    City cities[150];
    int numCities = 0;
    int totalCost = 0;
    int minCost = 0;
    int minIndex = -1;

    // 读取输入数据
    while (scanf("%d %d %s", &cities[numCities].students, &cities[numCities].distance, cities[numCities].name) == 3) {
        numCities++;
    }

    // 计算总人数
    int totalStudents = 0;
    for (int i = 0; i < numCities; i++) {
        totalStudents += cities[i].students;
    }

    // 计算每个城市到其他城市的单程旅行费用
    for (int i = 0; i < numCities; i++) {
        int cost = 0;
        for (int j = 0; j < numCities; j++) {
            if (i != j) {
                cost += cities[j].students * abs(cities[i].distance - cities[j].distance);
            }
        }
        totalCost += cost;
        if (minIndex == -1 || cost < minCost) {
            minCost = cost;
            minIndex = i;
        }
    }

    // 输出结果
    printf("%s %d\n", cities[minIndex].name, totalCost / 2);

    return 0;
}