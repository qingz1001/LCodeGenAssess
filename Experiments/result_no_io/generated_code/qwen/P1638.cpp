#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000001
#define MAX_M 2004

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int paintings[MAX_N];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &paintings[i]);
    }

    int min_cost = n;
    int start = -1;

    for (int i = 0; i < m; ++i) {
        int first = -1, last = -1;
        for (int j = 0; j < n; ++j) {
            if (paintings[j] == i + 1) {
                if (first == -1) {
                    first = j;
                }
                last = j;
            }
        }
        if (first != -1 && last != -1) {
            int cost = last - first + 1;
            if (cost < min_cost || (cost == min_cost && first < start)) {
                min_cost = cost;
                start = first;
            }
        }
    }

    printf("%d %d\n", start + 1, start + min_cost);
    return 0;
}