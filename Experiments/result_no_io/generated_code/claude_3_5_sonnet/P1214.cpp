#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_M 250
#define MAX_SQUARES (MAX_M * MAX_M * 2 + 1)

int squares[MAX_SQUARES];
int squareCount = 0;
int n, m;

typedef struct {
    int a, b;
} Sequence;

Sequence sequences[10000];
int sequenceCount = 0;

int compare(const void* a, const void* b) {
    Sequence* sa = (Sequence*)a;
    Sequence* sb = (Sequence*)b;
    if (sa->b != sb->b) {
        return sa->b - sb->b;
    }
    return sa->a - sb->a;
}

void generateSquares() {
    for (int p = 0; p <= m; p++) {
        for (int q = p; q <= m; q++) {
            int square = p * p + q * q;
            if (square > squares[squareCount - 1]) {
                squares[squareCount++] = square;
            }
        }
    }
}

void findSequences() {
    for (int i = 0; i < squareCount; i++) {
        for (int j = i + 1; j < squareCount; j++) {
            int a = squares[i];
            int b = squares[j] - squares[i];
            int count = 2;
            int next = squares[j] + b;
            
            while (count < n) {
                int* found = bsearch(&next, squares, squareCount, sizeof(int), 
                                     (int (*)(const void*, const void*))strcmp);
                if (!found) break;
                count++;
                next += b;
            }
            
            if (count == n) {
                sequences[sequenceCount].a = a;
                sequences[sequenceCount].b = b;
                sequenceCount++;
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    
    generateSquares();
    findSequences();
    
    if (sequenceCount == 0) {
        printf("NONE\n");
    } else {
        qsort(sequences, sequenceCount, sizeof(Sequence), compare);
        for (int i = 0; i < sequenceCount; i++) {
            printf("%d %d\n", sequences[i].a, sequences[i].b);
        }
    }
    
    return 0;
}