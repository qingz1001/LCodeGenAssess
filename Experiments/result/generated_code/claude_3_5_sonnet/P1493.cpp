#include <stdio.h>
#include <stdlib.h>

#define MAX_N 2000

typedef struct {
    int A;
    int B;
} Pear;

int compare(const void* a, const void* b) {
    return ((Pear*)a)->A - ((Pear*)b)->A;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int N, C1, C2, C3;
    Pear pears[MAX_N];
    
    scanf("%d", &N);
    scanf("%d %d %d", &C1, &C2, &C3);
    
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &pears[i].A, &pears[i].B);
    }
    
    qsort(pears, N, sizeof(Pear), compare);
    
    int maxCount = 0;
    for (int i = 0; i < N; i++) {
        int count = 0;
        int A0 = pears[i].A;
        int B0 = pears[i].B;
        
        for (int j = i; j < N; j++) {
            if (C1 * (pears[j].A - A0) + C2 * (max(0, pears[j].B - B0)) <= C3) {
                count++;
            }
        }
        
        if (count > maxCount) {
            maxCount = count;
        }
    }
    
    printf("%d\n", maxCount);
    
    return 0;
}