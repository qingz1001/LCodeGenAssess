#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_L 1000000
#define MAX_A 1000
#define MAX_B 1000

typedef struct {
    int start;
    int end;
} CowField;

int compare(const void *a, const void *b) {
    CowField *fieldA = (CowField *)a;
    CowField *fieldB = (CowField *)b;
    return fieldA->start - fieldB->start;
}

int main() {
    int N, L, A, B;
    scanf("%d %d", &N, &L);
    scanf("%d %d", &A, &B);

    CowField fields[MAX_N];
    for (int i = 0; i < N; ++i) {
        scanf("%d %d", &fields[i].start, &fields[i].end);
    }

    qsort(fields, N, sizeof(CowField), compare);

    int numSprinklers = 0;
    int currentEnd = 0;

    for (int i = 0; i < N; ++i) {
        if (fields[i].start > currentEnd) {
            if (currentEnd == 0) {
                printf("-1\n");
                return 0;
            }
            numSprinklers++;
            currentEnd += B + 1;
        }
        currentEnd = fmax(currentEnd, fields[i].end);
    }

    if (currentEnd < L) {
        if (currentEnd == 0) {
            printf("-1\n");
            return 0;
        }
        numSprinklers++;
    }

    printf("%d\n", numSprinklers);
    return 0;
}