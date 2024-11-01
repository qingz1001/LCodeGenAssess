#include <stdio.h>
#include <math.h>

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        int a0, a1, b0, b1;
        scanf("%d%d%d%d", &a0, &a1, &b0, &b1);
        
        int x = lcm(a0, a1);
        int y = gcd(b0, b1);
        
        if (x % y != 0) {
            printf("0\n");
        } else {
            int count = 0;
            for (int i = 1; i * i <= x; i++) {
                if (x % i == 0) {
                    if (gcd(i, a1) == a1 && lcm(i, b0) == b1) count++;
                    if (i != x / i && gcd(x / i, a1) == a1 && lcm(x / i, b0) == b1) count++;
                }
            }
            printf("%d\n", count);
        }
    }
    return 0;
}