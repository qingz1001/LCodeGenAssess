#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int N, D;
int chocolates[50001];
int schedule[50001];

int canAchieveMinHappiness(long long minHappiness) {
    long long currentHappiness = 0;
    int day = 1;
    for (int i = 0; i < N; i++) {
        if (currentHappiness < minHappiness) {
            currentHappiness += chocolates[i];
            schedule[i] = day;
        } else {
            currentHappiness = chocolates[i];
            schedule[i] = ++day;
        }
        if (day > D) return 0;
        currentHappiness /= 2;
    }
    return 1;
}

int main() {
    scanf("%d %d", &N, &D);
    for (int i = 0; i < N; i++) {
        scanf("%d", &chocolates[i]);
    }

    long long left = 0, right = 1e12;
    long long bestMinHappiness = 0;

    while (left <= right) {
        long long mid = (left + right) / 2;
        if (canAchieveMinHappiness(mid)) {
            bestMinHappiness = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    canAchieveMinHappiness(bestMinHappiness);

    printf("%lld\n", bestMinHappiness);
    for (int i = 0; i < N; i++) {
        printf("%d\n", schedule[i]);
    }

    return 0;
}