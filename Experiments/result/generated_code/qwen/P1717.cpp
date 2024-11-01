#include <stdio.h>
#include <stdlib.h>

#define MAX_N 25
#define MAX_H 16

int main() {
    int n, h;
    scanf("%d %d", &n, &h);
    int f[MAX_N], d[MAX_N];
    int t[MAX_N - 1];
    
    for (int i = 0; i < n; ++i) {
        scanf("%d", &f[i]);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", &d[i]);
    }
    for (int i = 0; i < n - 1; ++i) {
        scanf("%d", &t[i]);
    }

    int max_fish = 0;
    for (int start = 0; start < n; ++start) {
        int total_time = 0;
        int current_fish = 0;
        int remaining_time = h * 60;

        for (int end = start; end < n; ++end) {
            if (total_time + 5 * t[end] > remaining_time) break;
            total_time += 5 * t[end];
            current_fish += f[end];
            if (end != start) {
                current_fish -= (total_time / 5 - 1) * d[end];
            }
            max_fish = current_fish > max_fish ? current_fish : max_fish;
        }
    }

    printf("%d\n", max_fish);

    return 0;
}