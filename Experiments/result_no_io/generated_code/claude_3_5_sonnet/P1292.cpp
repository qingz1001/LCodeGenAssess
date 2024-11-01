#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void solve(int a, int b) {
    int c = gcd(a, b);
    int pa = b / c - 1;
    int pb = (a / c) * (b / c - 1) + 1;
    
    printf("%d\n", c);
    printf("%d %d\n", pa, pb);
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    
    solve(a, b);
    
    return 0;
}