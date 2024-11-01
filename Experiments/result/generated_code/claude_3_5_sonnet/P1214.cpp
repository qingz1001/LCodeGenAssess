#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXM 250
#define MAXN 25
#define MAXSQ 62500 // MAXM * MAXM

int n, m;
int squares[MAXSQ];
int sq_count = 0;
int results[10000][2];
int result_count = 0;

void generate_squares() {
    for (int p = 0; p <= m; p++) {
        for (int q = 0; q <= m; q++) {
            int sq = p*p + q*q;
            if (sq > squares[sq_count-1]) {
                squares[sq_count++] = sq;
            }
        }
    }
}

int compare(const void *a, const void *b) {
    int *x = (int*)a;
    int *y = (int*)b;
    if (x[1] != y[1]) return x[1] - y[1];
    return x[0] - y[0];
}

void find_progressions() {
    for (int i = 0; i < sq_count; i++) {
        for (int j = i+1; j < sq_count; j++) {
            int a = squares[i];
            int b = squares[j] - squares[i];
            int count = 2;
            int next = squares[j] + b;
            
            while (count < n) {
                int *found = bsearch(&next, squares, sq_count, sizeof(int), 
                                     (int (*)(const void*, const void*))strcmp);
                if (!found) break;
                count++;
                next += b;
            }
            
            if (count == n) {
                results[result_count][0] = a;
                results[result_count][1] = b;
                result_count++;
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    
    generate_squares();
    find_progressions();
    
    if (result_count == 0) {
        printf("NONE\n");
    } else {
        qsort(results, result_count, sizeof(results[0]), compare);
        for (int i = 0; i < result_count; i++) {
            printf("%d %d\n", results[i][0], results[i][1]);
        }
    }
    
    return 0;
}