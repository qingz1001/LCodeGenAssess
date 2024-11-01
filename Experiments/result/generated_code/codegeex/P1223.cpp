#include <stdio.h>
#include <stdlib.h>

// 定义一个结构体来存储每个人的编号和接水时间
typedef struct {
    int id;
    int time;
} Person;

// 比较函数，用于按接水时间从小到大排序
int compare(const void *a, const void *b) {
    Person *personA = (Person *)a;
    Person *personB = (Person *)b;
    return personA->time - personB->time;
}

int main() {
    int n;
    scanf("%d", &n);

    // 动态分配数组存储每个人的编号和接水时间
    Person *people = (Person *)malloc(n * sizeof(Person));

    for (int i = 0; i < n; i++) {
        people[i].id = i + 1;
        scanf("%d", &people[i].time);
    }

    // 按接水时间从小到大排序
    qsort(people, n, sizeof(Person), compare);

    // 输出排队顺序
    for (int i = 0; i < n; i++) {
        printf("%d ", people[i].id);
    }
    printf("\n");

    // 计算平均等待时间
    double totalWaitTime = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            totalWaitTime += people[j].time;
        }
    }
    double averageWaitTime = totalWaitTime / n;

    // 输出平均等待时间，保留两位小数
    printf("%.2f\n", averageWaitTime);

    // 释放动态分配的内存
    free(people);

    return 0;
}