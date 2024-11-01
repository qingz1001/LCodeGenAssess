#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 100000

int compare(const void *a, const void *b) {
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
    
    qsort(schools, m, sizeof(int), compare);
    qsort(students, n, sizeof(int), compare);
    
    long long total_dissatisfaction = 0;
    int school_index = 0;
    
    for (int i = 0; i < n; i++) {
        int student_score = students[i];
        int best_diff = abs(student_score - schools[school_index]);
        
        while (school_index + 1 < m && 
               abs(student_score - schools[school_index + 1]) <= best_diff) {
            school_index++;
            best_diff = abs(student_score - schools[school_index]);
        }
        
        total_dissatisfaction += best_diff;
    }
    
    printf("%lld\n", total_dissatisfaction);
    
    return 0;
}