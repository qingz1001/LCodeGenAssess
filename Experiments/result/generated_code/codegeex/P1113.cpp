#include <stdio.h>

#define MAX_TASKS 10001

int main() {
    int n;
    scanf("%d", &n);

    int tasks[MAX_TASKS][2] = {0}; // tasks[i][0] is the time to complete the task, tasks[i][1] is the number of prerequisites
    int prerequisites[MAX_TASKS][101] = {0}; // prerequisites[i][j] is the j-th prerequisite of task i

    // Read the input data
    for (int i = 1; i <= n; i++) {
        int taskNumber;
        scanf("%d", &taskNumber);
        scanf("%d", &tasks[taskNumber][0]);
        int prerequisite;
        while (scanf("%d", &prerequisite) && prerequisite != 0) {
            prerequisites[taskNumber][++tasks[taskNumber][1]] = prerequisite;
        }
    }

    int maxTime = 0;

    // Calculate the earliest time each task can start
    for (int i = 1; i <= n; i++) {
        int currentTime = 0;
        for (int j = 1; j <= tasks[i][1]; j++) {
            int prerequisite = prerequisites[i][j];
            if (tasks[prerequisite][2] + tasks[prerequisite][0] > currentTime) {
                currentTime = tasks[prerequisite][2] + tasks[prerequisite][0];
            }
        }
        tasks[i][2] = currentTime; // tasks[i][2] is the earliest time the task can start
        if (tasks[i][2] + tasks[i][0] > maxTime) {
            maxTime = tasks[i][2] + tasks[i][0];
        }
    }

    printf("%d\n", maxTime);

    return 0;
}