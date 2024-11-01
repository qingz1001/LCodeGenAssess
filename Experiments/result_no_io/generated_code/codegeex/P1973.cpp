#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200
#define MAX_TIME 1000000000

typedef struct {
    int start;
    int end;
} Activity;

int compare(const void *a, const void *b) {
    Activity *activityA = (Activity *)a;
    Activity *activityB = (Activity *)b;
    return activityA->start - activityB->start;
}

int main() {
    int n;
    scanf("%d", &n);

    Activity activities[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &activities[i].start, &activities[i].end);
    }

    qsort(activities, n, sizeof(Activity), compare);

    int dp1[MAX_TIME + 1], dp2[MAX_TIME + 1];
    for (int i = 0; i <= MAX_TIME; i++) {
        dp1[i] = dp2[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        for (int j = MAX_TIME; j >= activities[i].start; j--) {
            dp1[j] = (dp1[j] > dp1[j - activities[i].end] + 1) ? dp1[j] : dp1[j - activities[i].end] + 1;
        }
        for (int j = MAX_TIME; j >= activities[i].start; j--) {
            dp2[j] = (dp2[j] > dp2[j - activities[i].end] + 1) ? dp2[j] : dp2[j - activities[i].end] + 1;
        }
    }

    int max_activities = 0;
    for (int i = 0; i <= MAX_TIME; i++) {
        max_activities = (max_activities > dp1[i] + dp2[MAX_TIME - i]) ? max_activities : dp1[i] + dp2[MAX_TIME - i];
    }

    printf("%d\n", max_activities);

    for (int i = 0; i < n; i++) {
        int dp1_with_i[MAX_TIME + 1], dp2_with_i[MAX_TIME + 1];
        for (int j = 0; j <= MAX_TIME; j++) {
            dp1_with_i[j] = dp2_with_i[j] = 0;
        }

        for (int j = 0; j <= i; j++) {
            for (int k = MAX_TIME; k >= activities[j].start; k--) {
                dp1_with_i[k] = (dp1_with_i[k] > dp1_with_i[k - activities[j].end] + 1) ? dp1_with_i[k] : dp1_with_i[k - activities[j].end] + 1;
            }
        }

        for (int j = i + 1; j < n; j++) {
            for (int k = MAX_TIME; k >= activities[j].start; k--) {
                dp2_with_i[k] = (dp2_with_i[k] > dp2_with_i[k - activities[j].end] + 1) ? dp2_with_i[k] : dp2_with_i[k - activities[j].end] + 1;
            }
        }

        int max_activities_with_i = 0;
        for (int j = 0; j <= MAX_TIME; j++) {
            max_activities_with_i = (max_activities_with_i > dp1_with_i[j] + dp2_with_i[MAX_TIME - j]) ? max_activities_with_i : dp1_with_i[j] + dp2_with_i[MAX_TIME - j];
        }

        printf("%d\n", max_activities_with_i);
    }

    return 0;
}