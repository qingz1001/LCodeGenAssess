#include <stdio.h>
#include <limits.h>

int main() {
    int n;
    scanf("%d", &n);

    int packages[3][2];
    for (int i = 0; i < 3; i++) {
        scanf("%d %d", &packages[i][0], &packages[i][1]);
    }

    int min_cost = INT_MAX;

    for (int i = 0; i < 3; i++) {
        int num_packages = (n + packages[i][0] - 1) / packages[i][0];
        int cost = num_packages * packages[i][1];
        if (cost < min_cost) {
            min_cost = cost;
        }
    }

    printf("%d\n", min_cost);

    return 0;
}