#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define MAX_NAME_LEN 20

int main() {
    int n;
    char names[MAX_N][MAX_NAME_LEN + 1];
    int counts[MAX_N] = {0};
    int total_reminders = 0;

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", names[i]);
    }

    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < i; j++) {
            if (strcmp(names[i], names[j]) == 0) {
                count++;
            }
        }
        counts[i] = count;
    }

    for (int i = 0; i < n; i++) {
        int others_count = 0;
        for (int j = 0; j < i; j++) {
            if (strcmp(names[i], names[j]) != 0) {
                others_count += counts[j];
            }
        }
        if (counts[i] > others_count) {
            total_reminders++;
        }
    }

    printf("%d\n", total_reminders);

    return 0;
}