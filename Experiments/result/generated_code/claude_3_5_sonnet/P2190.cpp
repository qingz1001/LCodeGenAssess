#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000001

int diff[MAX_N];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    memset(diff, 0, sizeof(diff));

    for (int i = 0; i < m; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        x--; y--;  // 将站点编号转为0-based
        if (x < y) {
            diff[x] += z;
            diff[y] -= z;
        } else {
            diff[x] += z;
            diff[0] += z;
            diff[y] -= z;
        }
    }

    int max_passengers = 0;
    int current_passengers = 0;
    for (int i = 0; i < n; i++) {
        current_passengers += diff[i];
        if (current_passengers > max_passengers) {
            max_passengers = current_passengers;
        }
    }

    int carriages = (max_passengers + 35) / 36;  // 向上取整
    printf("%d\n", carriages);

    return 0;
}