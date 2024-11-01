#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200
#define MAX_TIME 1000000000

typedef struct {
    int start;
    int end;
} Activity;

int compare(const void *a, const void *b) {
    return ((Activity *)a)->start - ((Activity *)b)->start;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

void solve(int n, Activity activities[], int results[]) {
    int events[MAX_N * 2];
    for (int i = 0; i < n; i++) {
        events[i * 2] = activities[i].start;
        events[i * 2 + 1] = activities[i].end;
    }
    qsort(events, n * 2, sizeof(int), (int (*)(const void *, const void *))compare);

    int count[2] = {0};
    int last_time[2] = {-1, -1};
    for (int i = 0; i < n * 2; i += 2) {
        if (events[i] != last_time[0]) {
            count[0]++;
            last_time[0] = events[i];
        }
        if (events[i + 1] != last_time[1]) {
            count[1]++;
            last_time[1] = events[i + 1];
        }
    }

    results[0] = max(count[0], count[1]);
    for (int i = 0; i < n; i++) {
        int current_count[2] = {count[0], count[1]};
        int activity_start = activities[i].start;
        int activity_end = activities[i].end;

        if (activity_start == last_time[0]) {
            current_count[0]--;
        } else {
            current_count[0]++;
            last_time[0] = activity_start;
        }

        if (activity_end == last_time[1]) {
            current_count[1]--;
        } else {
            current_count[1]++;
            last_time[1] = activity_end;
        }

        results[i + 1] = max(current_count[0], current_count[1]);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    Activity activities[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &activities[i].start, &activities[i].end);
    }

    int results[MAX_N + 1];
    solve(n, activities, results);

    printf("%d\n", results[0]);
    for (int i = 0; i < n; i++) {
        printf("%d\n", results[i + 1]);
    }

    return 0;
}