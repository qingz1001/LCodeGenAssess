#include <stdio.h>
#include <stdlib.h>

typedef struct Chocolate {
    int happiness;
    int day;
} Chocolate;

int compare(const void *a, const void *b) {
    Chocolate *chocolateA = (Chocolate *)a;
    Chocolate *chocolateB = (Chocolate *)b;
    return chocolateB->happiness - chocolateA->happiness;
}

int main() {
    int N, D;
    scanf("%d %d", &N, &D);

    Chocolate chocolates[N];
    int totalHappiness = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d", &chocolates[i].happiness);
        chocolates[i].day = 0;
        totalHappiness += chocolates[i].happiness;
    }

    qsort(chocolates, N, sizeof(Chocolate), compare);

    int left = 0, right = totalHappiness / D, mid;
    int result = 0, resultDay[N + 1];

    while (left <= right) {
        mid = (left + right) / 2;
        int happiness = 0, day = 0;
        int i;
        for (i = 0; i < N; i++) {
            if (happiness + chocolates[i].happiness > mid) {
                break;
            }
            happiness += chocolates[i].happiness;
            day++;
        }

        if (day >= D) {
            result = mid;
            for (int j = 0; j < i; j++) {
                resultDay[j] = day;
            }
            for (int j = i; j < N; j++) {
                resultDay[j] = day - 1;
            }
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    printf("%d\n", result);
    for (int i = 0; i < N; i++) {
        printf("%d\n", resultDay[i]);
    }

    return 0;
}