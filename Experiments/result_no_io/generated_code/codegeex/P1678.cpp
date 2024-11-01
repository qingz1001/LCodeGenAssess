#include <stdio.h>
#include <stdlib.h>

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    
    int *school_scores = (int *)malloc(m * sizeof(int));
    int *student_scores = (int *)malloc(n * sizeof(int));
    
    for (int i = 0; i < m; i++) {
        scanf("%d", &school_scores[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &student_scores[i]);
    }
    
    // Sort the arrays
    qsort(school_scores, m, sizeof(int), (int (*)(const void *, const void *))cmp);
    qsort(student_scores, n, sizeof(int), (int (*)(const void *, const void *))cmp);
    
    int min_dis_sum = 0;
    int left = 0, right = 0;
    
    // Use two pointers to find the closest school for each student
    while (left < n && right < m) {
        if (abs(school_scores[right] - student_scores[left]) < abs(school_scores[right + 1] - student_scores[left])) {
            min_dis_sum += abs(school_scores[right] - student_scores[left]);
            left++;
        } else {
            min_dis_sum += abs(school_scores[right + 1] - student_scores[left]);
            right++;
        }
    }
    
    printf("%d\n", min_dis_sum);
    
    free(school_scores);
    free(student_scores);
    
    return 0;
}

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}