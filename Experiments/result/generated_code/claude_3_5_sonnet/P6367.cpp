#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define MAX_NAME_LEN 21

int main() {
    int n, count = 0;
    char names[MAX_N][MAX_NAME_LEN];
    int taken[MAX_N] = {0};

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%s", names[i]);
    }

    for (int i = 0; i < n; i++) {
        int current_child = -1;
        int others_sum = 0;

        for (int j = 0; j < n; j++) {
            if (strcmp(names[i], names[j]) == 0) {
                current_child = j;
                break;
            }
        }

        for (int j = 0; j < n; j++) {
            if (j != current_child) {
                others_sum += taken[j];
            }
        }

        if (taken[current_child] > others_sum) {
            count++;
        }

        taken[current_child]++;
    }

    printf("%d\n", count);

    return 0;
}