#include <stdio.h>
#include <stdlib.h>

#define MAX_COMMANDS 300000
#define MAX_ADJUSTMENTS 100
#define MIN_WAGE 0

typedef struct {
    int salary;
    int index;
} Employee;

int compare(const void *a, const void *b) {
    return ((Employee *)b)->salary - ((Employee *)a)->salary;
}

int main() {
    int n, min;
    scanf("%d %d", &n, &min);

    Employee employees[MAX_COMMANDS];
    int adjustment[MAX_ADJUSTMENTS][2];
    int adjustment_count = 0;

    for (int i = 0; i < n; i++) {
        char command;
        int k;
        scanf(" %c %d", &command, &k);

        if (command == 'I') {
            if (k >= min) {
                employees[adjustment_count].salary = k;
                employees[adjustment_count].index = adjustment_count;
                adjustment_count++;
            }
        } else if (command == 'A' || command == 'S') {
            adjustment[adjustment_count / 2][0] = command == 'A' ? k : -k;
            adjustment[adjustment_count / 2][1] = adjustment_count / 2;
            adjustment_count++;
        } else if (command == 'F') {
            qsort(employees, adjustment_count, sizeof(Employee), compare);
            if (k > adjustment_count) {
                printf("-1\n");
            } else {
                printf("%d\n", employees[k - 1].salary);
            }
        }
    }

    printf("%d\n", adjustment_count);

    return 0;
}