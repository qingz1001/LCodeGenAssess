#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    if (n <= 2 || m <= 2) {
        printf("0\n");
        return 0;
    }
    
    int count = 0;
    for (int i = 2; i < n - 1; i++) {
        for (int j = 2; j < m - 1; j++) {
            count++;
        }
    }
    
    printf("%d\n", count);
    return 0;
}