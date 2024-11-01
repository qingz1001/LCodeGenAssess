#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define MAX_NAME_LEN 21

int main() {
    int n;
    char names[MAX_N][MAX_NAME_LEN];
    int count[MAX_N] = {0};
    int total_reminders = 0;

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", names[i]);
    }

    for (int i = 0; i < n; i++) {
        int current_count = 0;
        for (int j = 0; j < i; j++) {
            if (strcmp(names[i], names[j]) == 0) {
                current_count++;
            }
        }
        count[i] = current_count;
    }

    for (int i = 0; i < n; i++) {
        int others_count = 0;
        for (int j = 0; j < n; j++) {
            if (strcmp(names[i], names[j]) != 0) {
                others_count += count[j];
            }
        }
        if (count[i] > others_count) {
            total_reminders++;
        }
    }

    printf("%d\n", total_reminders);
    return 0;
}