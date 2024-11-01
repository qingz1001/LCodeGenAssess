#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    
    if (k == 1) {
        printf("1\n");
        return 0;
    }
    
    int max_gcd = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            max_gcd = gcd(max_gcd, gcd(i, j));
        }
    }
    
    printf("%d\n", max_gcd);
    return 0;
}