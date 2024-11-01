#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000000

int main() {
    int n, s;
    scanf("%d %d", &n, &s);

    int distances[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d", &distances[i]);
    }

    for (int i = 0; i < s; i++) {
        int max_range;
        scanf("%d", &max_range);

        int min_landings = 0;
        int current_position = 0;

        while (current_position < n) {
            int farthest_position = current_position;
            while (farthest_position < n && distances[farthest_position] <= max_range) {
                farthest_position = (farthest_position + 1) % n;
                max_range -= distances[farthest_position];
            }

            if (farthest_position == current_position) {
                break;
            }

            min_landings++;
            current_position = farthest_position;
        }

        if (current_position == 0) {
            printf("NIE\n");
        } else {
            printf("%d\n", min_landings);
        }
    }

    return 0;
}