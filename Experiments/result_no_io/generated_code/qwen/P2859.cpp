#include <stdio.h>
#include <stdlib.h>

#define MAX_STALLS 50001
#define MAX_TIME 1000001

int main() {
    int N;
    scanf("%d", &N);

    int start[MAX_STALLS], end[MAX_STALLS];
    for (int i = 0; i < N; ++i) {
        scanf("%d %d", &start[i], &end[i]);
    }

    // Sort intervals by their end time
    for (int i = 0; i < N - 1; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (end[j] < end[i]) {
                int tempStart = start[i];
                start[i] = start[j];
                start[j] = tempStart;

                int tempEnd = end[i];
                end[i] = end[j];
                end[j] = tempEnd;
            }
        }
    }

    int stalls[MAX_STALLS] = {0};
    int min_stalls = 0;

    for (int i = 0; i < N; ++i) {
        int assigned = 0;
        for (int j = 0; j < min_stalls; ++j) {
            if (stalls[j] <= start[i]) {
                stalls[j] = end[i];
                assigned = 1;
                break;
            }
        }
        if (!assigned) {
            stalls[min_stalls++] = end[i];
        }
    }

    printf("%d\n", min_stalls);
    for (int i = 0; i < N; ++i) {
        int assigned = 0;
        for (int j = 0; j < min_stalls; ++j) {
            if (stalls[j] >= start[i]) {
                printf("%d\n", j + 1);
                assigned = 1;
                break;
            }
        }
    }

    return 0;
}