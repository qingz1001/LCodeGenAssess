#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 500005

int n;
double k;
int d[MAX_N], sorted[MAX_N], ans[MAX_N];

int cmp(const void *a, const void *b) {
    return *(int*)b - *(int*)a;
}

int main() {
    scanf("%d %lf", &n, &k);
    for(int i = 0; i < n; i++) {
        scanf("%d", &d[i]);
        sorted[i] = d[i];
    }

    qsort(sorted, n, sizeof(int), cmp);

    for(int i = n-1; i >= 0; i--) {
        int parent = floor(i / k);
        if(parent == i) {
            ans[i] = sorted[0];
        } else {
            ans[i] = sorted[n-1];
            for(int j = 0; j < n; j++) {
                if(sorted[j] <= ans[parent] && sorted[j] > ans[i]) {
                    ans[i] = sorted[j];
                    break;
                }
            }
        }
        for(int j = 0; j < n; j++) {
            if(sorted[j] == ans[i]) {
                sorted[j] = -1;
                break;
            }
        }
    }

    for(int i = 0; i < n; i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");

    return 0;
}