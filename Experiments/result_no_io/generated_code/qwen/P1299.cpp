#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_COORD 2001

int main() {
    int N;
    scanf("%d", &N);
    int x[MAX_N], y[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d %d", &x[i], &y[i], &x[i+1], &y[i+1]);
        if (x[i] > x[i+1]) {
            int temp = x[i];
            x[i] = x[i+1];
            x[i+1] = temp;
        }
        if (y[i] > y[i+1]) {
            int temp = y[i];
            y[i] = y[i+1];
            y[i+1] = temp;
        }
    }

    int holes[MAX_COORD][MAX_COORD] = {0};
    for (int i = 0; i < N; i += 2) {
        for (int j = x[i]; j <= x[i+1]; j++) {
            for (int k = y[i]; k <= y[i+1]; k++) {
                holes[j][k]++;
            }
        }
    }

    int result[N/2];
    int count = 0;
    for (int i = 0; i < N; i += 2) {
        int area = (x[i+1] - x[i]) * (y[i+1] - y[i]);
        if (area >= 1) {
            result[count++] = area;
        }
    }

    for (int i = 0; i < count; i++) {
        printf("%d\n", result[i]);
    }

    return 0;
}