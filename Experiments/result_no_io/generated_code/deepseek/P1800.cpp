#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 100
#define MAX_M 100

typedef struct {
    int d1;
    int d2;
} Technician;

int compare(const void *a, const void *b) {
    Technician *techA = (Technician *)a;
    Technician *techB = (Technician *)b;
    return (techA->d1 + techB->d2) - (techB->d1 + techA->d2);
}

int min_days(int n, int m, Technician techs[]) {
    qsort(techs, n, sizeof(Technician), compare);

    int left = 0, right = m * 100;
    while (left < right) {
        int mid = (left + right) / 2;
        int first_software_modules = 0;
        int second_software_modules = 0;

        for (int i = 0; i < n; i++) {
            int max_modules_per_tech = mid / techs[i].d1;
            first_software_modules += max_modules_per_tech;
            if (first_software_modules >= m) break;
        }

        for (int i = 0; i < n; i++) {
            int max_modules_per_tech = mid / techs[i].d2;
            second_software_modules += max_modules_per_tech;
            if (second_software_modules >= m) break;
        }

        if (first_software_modules >= m && second_software_modules >= m) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    return left;
}

int main() {
    int n, m;
    Technician techs[MAX_N];

    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &techs[i].d1, &techs[i].d2);
    }

    int result = min_days(n, m, techs);
    printf("%d\n", result);

    return 0;
}