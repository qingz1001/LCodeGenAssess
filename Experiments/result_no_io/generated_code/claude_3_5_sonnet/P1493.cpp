#include <stdio.h>
#include <stdlib.h>

#define MAX_N 2000

typedef struct {
    int A;
    int B;
} Pear;

Pear pears[MAX_N];
int N, C1, C2, C3;

int compare(const void *a, const void *b) {
    return ((Pear *)a)->A - ((Pear *)b)->A;
}

int check(int A0, int B0) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (C1 * (pears[i].A - A0) + C2 * (pears[i].B - B0) <= C3) {
            count++;
        }
    }
    return count;
}

int main() {
    scanf("%d", &N);
    scanf("%d %d %d", &C1, &C2, &C3);
    
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &pears[i].A, &pears[i].B);
    }
    
    qsort(pears, N, sizeof(Pear), compare);
    
    int max_count = 0;
    for (int i = 0; i < N; i++) {
        int A0 = pears[i].A;
        for (int j = 0; j < N; j++) {
            int B0 = pears[j].B;
            int count = check(A0, B0);
            if (count > max_count) {
                max_count = count;
            }
        }
    }
    
    printf("%d\n", max_count);
    
    return 0;
}