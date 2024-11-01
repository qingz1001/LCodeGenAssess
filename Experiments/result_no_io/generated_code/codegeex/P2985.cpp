#include <stdio.h>
#include <stdbool.h>

#define MAX_N 50000
#define MAX_H 1000000

int chocolates[MAX_N];
int happiness[MAX_N];
int days[MAX_N];

bool canDistribute(int n, int d, int maxHappiness) {
    int currentDay = 1;
    int totalHappiness = 0;
    int i = 0;

    while (i < n) {
        totalHappiness += chocolates[i];
        happiness[i] = totalHappiness;
        days[i] = currentDay;

        if (happiness[i] >= maxHappiness) {
            i++;
            totalHappiness = 0;
            currentDay++;
        } else {
            if (currentDay == d) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    int n, d;
    scanf("%d %d", &n, &d);

    for (int i = 0; i < n; i++) {
        scanf("%d", &chocolates[i]);
    }

    int left = 0, right = MAX_H * n;
    int result = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (canDistribute(n, d, mid)) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    printf("%d\n", result);

    canDistribute(n, d, result);

    for (int i = 0; i < n; i++) {
        printf("%d\n", days[i]);
    }

    return 0;
}