#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_P 10000

int main() {
    int N, Pi;
    scanf("%d %d", &N, &Pi);

    int items[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &items[i]);
    }

    int max_value = 0;

    for (int i = 0; i < N; i++) {
        if (items[i] > Pi) {
            max_value += items[i];
        } else {
            int value1 = items[i];
            int value2 = 0;
            for (int j = i + 1; j < N; j++) {
                if (items[j] > Pi && items[j] > value1) {
                    value2 = items[j];
                    break;
                }
            }
            if (value2 == 0) {
                max_value += value1;
            } else {
                max_value += value2 - Pi;
            }
        }
    }

    printf("%d\n", max_value);

    return 0;
}