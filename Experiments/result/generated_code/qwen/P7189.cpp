#include <stdio.h>

int main() {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);

    int times[3][2];
    for (int i = 0; i < 3; i++) {
        scanf("%d %d", &times[i][0], &times[i][1]);
    }

    int total_cost = 0;

    for (int i = 0; i < 101; i++) {
        int cars_parked = 0;
        for (int j = 0; j < 3; j++) {
            if (i >= times[j][0] && i < times[j][1]) {
                cars_parked++;
            }
        }
        if (cars_parked == 1) {
            total_cost += a;
        } else if (cars_parked == 2) {
            total_cost += b * 2;
        } else if (cars_parked == 3) {
            total_cost += c * 3;
        }
    }

    printf("%d\n", total_cost);

    return 0;
}