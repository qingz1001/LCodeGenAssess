#include <stdio.h>
#include <stdlib.h>

#define MAX_COMMANDS 300000
#define MAX_EMPLOYEES 100000

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

    Employee employees[MAX_EMPLOYEES];
    int employee_count = 0;
    int fired_count = 0;

    for (int i = 0; i < n; i++) {
        char command;
        int k;
        scanf(" %c %d", &command, &k);

        switch (command) {
            case 'I':
                if (k >= min) {
                    employees[employee_count].salary = k;
                    employees[employee_count].index = employee_count;
                    employee_count++;
                }
                break;
            case 'A':
                for (int j = 0; j < employee_count; j++) {
                    employees[j].salary += k;
                }
                qsort(employees, employee_count, sizeof(Employee), compare);
                break;
            case 'S':
                for (int j = 0; j < employee_count; j++) {
                    employees[j].salary -= k;
                }
                qsort(employees, employee_count, sizeof(Employee), compare);
                break;
            case 'F':
                if (k > employee_count) {
                    printf("-1\n");
                } else {
                    printf("%d\n", employees[k - 1].salary);
                }
                break;
        }
    }

    printf("%d\n", fired_count);

    return 0;
}