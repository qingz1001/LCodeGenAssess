#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int m, s, c;
    scanf("%d %d %d", &m, &s, &c);
    
    int stalls[c];
    for (int i = 0; i < c; i++) {
        scanf("%d", &stalls[i]);
    }
    
    qsort(stalls, c, sizeof(int), compare);
    
    int gaps[c - 1];
    for (int i = 0; i < c - 1; i++) {
        gaps[i] = stalls[i + 1] - stalls[i] - 1;
    }
    
    qsort(gaps, c - 1, sizeof(int), compare);
    
    int boards = 1;
    int total_length = stalls[c - 1] - stalls[0] + 1;
    
    for (int i = c - 2; i >= 0 && boards < m; i--, boards++) {
        total_length -= gaps[i];
    }
    
    printf("%d\n", total_length);
    
    return 0;
}