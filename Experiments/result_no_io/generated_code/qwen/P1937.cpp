#include <stdio.h>
#include <stdlib.h>

#define MAXN 100001

int n, m;
int capacities[MAXN];
int requests[MAXN][2];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &capacities[i]);
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d", &requests[i][0], &requests[i][1]);
    }

    int max_satisfied = 0;
    for (int start = 1; start <= n; ++start) {
        int current_capacity = 0;
        for (int end = start; end <= n; ++end) {
            if (current_capacity + capacities[end] > capacities[start]) {
                break;
            }
            current_capacity += capacities[end];
            int request_count = 0;
            for (int i = 1; i <= m; ++i) {
                if (requests[i][0] >= start && requests[i][1] <= end) {
                    ++request_count;
                }
            }
            max_satisfied = fmax(max_satisfied, request_count);
        }
    }

    printf("%d\n", max_satisfied);
    return 0;
}