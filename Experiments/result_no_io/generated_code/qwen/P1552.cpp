#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100005
#define MAX_M 1000000000

typedef struct {
    int boss;
    int salary;
    long long leadership;
} Ninja;

int compare(const void *a, const void *b) {
    Ninja *ninjaA = (Ninja *)a;
    Ninja *ninjaB = (Ninja *)b;
    return ninjaB->salary - ninjaA->salary;
}

long long maxSatisfaction(int n, int m, Ninja ninjas[]) {
    qsort(ninjas, n, sizeof(Ninja), compare);

    long long totalSalary = 0;
    long long satisfaction = 0;
    int dispatchedCount = 0;

    for (int i = 0; i < n && totalSalary + ninjas[i].salary <= m; ++i) {
        totalSalary += ninjas[i].salary;
        dispatchedCount++;
        satisfaction = (long long)dispatchedCount * ninjas[i].leadership;
    }

    return satisfaction;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Ninja ninjas[MAX_N];
    for (int i = 0; i < n; ++i) {
        scanf("%d %d %lld", &ninjas[i].boss, &ninjas[i].salary, &ninjas[i].leadership);
    }

    printf("%lld\n", maxSatisfaction(n, m, ninjas));

    return 0;
}