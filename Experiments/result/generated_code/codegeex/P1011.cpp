#include <stdio.h>

int main() {
    int a, n, m, x;
    scanf("%d %d %d %d", &a, &n, &m, &x);

    int people_on[21] = {0}; // 上车人数
    int people_off[21] = {0}; // 下车人数
    int car_people[21] = {0}; // 车上人数

    people_on[1] = a;
    car_people[1] = a;
    people_off[2] = a;
    car_people[2] = a;

    for (int i = 3; i < n; i++) {
        people_on[i] = people_on[i-1] + people_on[i-2];
        people_off[i] = people_on[i-1];
        car_people[i] = car_people[i-1] + people_on[i] - people_off[i];
    }

    printf("%d\n", car_people[x]);

    return 0;
}