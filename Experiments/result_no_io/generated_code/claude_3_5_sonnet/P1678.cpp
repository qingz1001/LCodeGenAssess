#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 100000

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int m, n;
    int schools[MAX_N], students[MAX_N];
    
    scanf("%d %d", &m, &n);
    
    for (int i = 0; i < m; i++) {
        scanf("%d", &schools[i]);
    }
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &students[i]);
    }
    
    qsort(schools, m, sizeof(int), cmp);
    qsort(students, n, sizeof(int), cmp);
    
    long long total_dissatisfaction = 0;
    int school_index = 0;
    
    for (int i = 0; i < n; i++) {
        while (school_index < m - 1 && 
               abs(schools[school_index + 1] - students[i]) <= abs(schools[school_index] - students[i])) {
            school_index++;
        }
        total_dissatisfaction += abs(schools[school_index] - students[i]);
    }
    
    printf("%lld\n", total_dissatisfaction);
    
    return 0;
}