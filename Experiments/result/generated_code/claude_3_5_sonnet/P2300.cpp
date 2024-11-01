#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200000

long long p[MAX_N];
int n;

int main() {
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%lld", &p[i]);
    }
    
    int merges = 0;
    int i = 0;
    
    while (i < n - 1) {
        if (p[i] > p[i+1]) {
            if (i > 0) {
                p[i-1] += p[i];
                for (int j = i; j < n - 1; j++) {
                    p[j] = p[j+1];
                }
                n--;
                i--;
            } else {
                p[i+1] += p[i];
                for (int j = i; j < n - 1; j++) {
                    p[j] = p[j+1];
                }
                n--;
            }
            merges++;
        } else {
            i++;
        }
    }
    
    printf("%d\n", merges);
    
    return 0;
}