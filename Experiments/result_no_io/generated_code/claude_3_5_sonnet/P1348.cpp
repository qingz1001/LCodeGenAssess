#include <stdio.h>
#include <math.h>

int isCouple(int n) {
    if (n <= 0) return 0;
    int root = (int)sqrt(n);
    for (int x = root; x > 0; x--) {
        int y = (int)sqrt(x * x - n);
        if (x * x - y * y == n) return 1;
    }
    return 0;
}

int main() {
    int a, b, count = 0;
    scanf("%d %d", &a, &b);
    
    for (int i = a; i <= b; i++) {
        if (isCouple(i)) count++;
    }
    
    printf("%d\n", count);
    return 0;
}