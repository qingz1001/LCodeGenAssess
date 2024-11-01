#include <stdio.h>
#include <stdlib.h>

#define MAX_M 100005

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    
    int accounts[MAX_M];
    for (int i = 0; i < m; ++i) {
        scanf("%d", &accounts[i]);
    }
    
    for (int i = 0; i < n; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        int min_value = accounts[a - 1];
        for (int j = a; j <= b; ++j) {
            if (accounts[j - 1] < min_value) {
                min_value = accounts[j - 1];
            }
        }
        printf("%d ", min_value);
    }
    
    return 0;
}