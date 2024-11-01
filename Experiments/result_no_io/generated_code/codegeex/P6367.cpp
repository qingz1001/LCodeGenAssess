#include <stdio.h>
#include <string.h>

int main() {
    int n, max = 0, count = 0, reminders = 0;
    char name[21];

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%s", name);
        if (i == 0) {
            max = 1;
        } else {
            if (strcmp(name, "other") != 0) {
                count++;
            }
            if (count > max) {
                max = count;
            }
            if (count < max) {
                reminders++;
            }
        }
    }

    printf("%d\n", reminders);

    return 0;
}