#include <stdio.h>
#include <stdlib.h>

#define MAX_N 50

int n, L, R;
int students[MAX_N];

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int i, total = 0, moves = 0;
    
    scanf("%d", &n);
    
    for (i = 0; i < n; i++) {
        scanf("%d", &students[i]);
        total += students[i];
    }
    
    scanf("%d %d", &L, &R);
    
    if (total < n * L || total > n * R) {
        printf("-1\n");
        return 0;
    }
    
    qsort(students, n, sizeof(int), compare);
    
    for (i = 0; i < n; i++) {
        if (students[i] < L) {
            moves += L - students[i];
        }
    }
    
    for (i = n - 1; i >= 0 && total > n * L; i--) {
        if (students[i] > R) {
            int excess = students[i] - R;
            moves += excess;
            total -= excess;
        }
    }
    
    printf("%d\n", moves);
    
    return 0;
}